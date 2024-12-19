#ifndef SARMSTABLE_H
#define SARMSTABLE_H

class Result
{
public:
    struct Column
    {
        string label;
        Column(const string &lbl) : label(lbl) {}
        string get_column_label() const { return label; }
    };

    struct Row
    {
        vector<string> data;
        Row(const vector<string> &d) : data(d) {}
        string get_as_string(size_t index) const { return data[index]; }
    };

    vector<Column> columns;
    vector<Row> rows;
    size_t current_row;

    Result(MYSQL_RES *result) : current_row(0)
    {
        MYSQL_FIELD *fields = mysql_fetch_fields(result);
        int num_fields = mysql_num_fields(result);
        for (int i = 0; i < num_fields; ++i)
        {
            columns.emplace_back(fields[i].name);
        }
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)))
        {
            vector<string> row_data;
            for (int i = 0; i < num_fields; ++i)
            {
                row_data.emplace_back(row[i] ? row[i] : "NULL");
            }
            rows.emplace_back(row_data);
        }
    }

    vector<Column> get_metadata() const { return columns; }
    unique_ptr<Row> fetch_one()
    {
        if (current_row < rows.size())
        {
            return make_unique<Row>(rows[current_row++]);
        }
        return nullptr;
    }
};

class Field_formatter
{
private:
    string m_buffer;
    string m_header;
    size_t m_max_display_length;

public:
    Field_formatter(const Result::Column &column)
        : m_max_display_length(column.get_column_label().length()), m_header(column.get_column_label()) {}

    void process(const Result::Row *row, size_t index)
    {
        size_t length = row->get_as_string(index).length();
        if (length > m_max_display_length)
        {
            m_max_display_length = length;
        }
    }

    bool put(const Result::Row *row, size_t index)
    {
        m_buffer = row->get_as_string(index);
        return true;
    }

    string str() const { return m_buffer; }
    string header() const { return m_header; }
    size_t get_max_display_length() const { return m_max_display_length; }
};

class Printer
{
public:
    void print(const string &s) { cout << s; }
};

class Resultset_dumper_base
{
private:
    Result *m_result;
    Printer *m_printer;
    bool m_cancelled;

public:
    Resultset_dumper_base(Result *result, Printer *printer) : m_result(result), m_printer(printer), m_cancelled(false) {}

    size_t dump_table()
    {
        const auto &metadata = m_result->get_metadata();
        vector<Field_formatter> fmt;
        vector<Result::Row> pre_fetched_rows;
        size_t num_records = 0;
        const size_t field_count = metadata.size();
        if (field_count == 0)
            return 0;

        for (size_t field_index = 0; field_index < field_count; field_index++)
        {
            fmt.emplace_back(metadata[field_index]);
        }

        auto row = m_result->fetch_one();
        while (row && !m_cancelled)
        {
            pre_fetched_rows.push_back(*row);
            for (size_t field_index = 0; field_index < field_count; field_index++)
            {
                fmt[field_index].process(row.get(), field_index);
            }
            row = m_result->fetch_one();
        }
        if (m_cancelled || pre_fetched_rows.empty())
            return 0;

        string separator("+");
        for (size_t index = 0; index < field_count; index++)
        {
            separator.append(string(fmt[index].get_max_display_length() + 2, '-')).append("+");
        }
        separator.append("\n");

        m_printer->print(separator);
        m_printer->print("| ");
        for (size_t index = 0; index < field_count; index++)
        {
            m_printer->print(fmt[index].header() + string(fmt[index].get_max_display_length() - fmt[index].header().length(), ' ') + " | ");
        }
        m_printer->print("\n" + separator);

        for (const auto &row : pre_fetched_rows)
        {
            ++num_records;
            m_printer->print("| ");
            for (size_t field_index = 0; field_index < field_count; field_index++)
            {
                fmt[field_index].put(&row, field_index);
                m_printer->print(fmt[field_index].str() + string(fmt[field_index].get_max_display_length() - fmt[field_index].str().length(), ' ') + " | ");
            }
            m_printer->print("\n");
            if (m_cancelled)
                break;
        }

        m_printer->print(separator);
        return num_records;
    }
};

#endif // RESULT_PRINTER_H
