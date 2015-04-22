using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Excel;
using System.IO;

namespace DataReader
{
    public class DataEntry
    {
        public DataEntry(string ColumnName)
        {
            this.ColumnName = ColumnName;
            Data = new List<string>();
            NumberRange = new Tuple<double, double>(-1, -1);
            AllNumbers = false;
            UniquEntries = -1;
        }

        public string ColumnName;
        public List<string> Data;

        public int UniquEntries;

        public bool AllNumbers;
        public Tuple<double, double> NumberRange;
    }

    public class ExcelReader
    {
        public List<DataEntry> ds;

        public ExcelReader(string fileName)
        {
            ds = new List<DataEntry>();

            if (fileName.IndexOf(".txt") != -1)
            {
                readFromText(fileName);
            }
            else
            {
                readFromExcel(fileName);
            }
        }

        void readFromText(string fileName)
        {
            string[] dataFile = File.ReadAllLines(fileName);

            foreach (var columnName in dataFile[0].Trim('\t').Replace("\t\t","\t[NONE]\t").Split('\t'))
            {
                ds.Add(new DataEntry(columnName));
            }

            for (int i = 1; i < dataFile.Length; ++i)
            {
                string[] entries = dataFile[i].Trim('\t').Replace("\t\t", "\t[NONE]\t").Split('\t');

                if (entries.Length == 0)
                {
                    continue;
                }

                for (int j = 0; j < entries.Length; ++j)
                {
                    ds[j].Data.Add(entries[j]);

                    int parseValue;
                    ds[j].AllNumbers = ds[j].AllNumbers && (Int32.TryParse(entries[j], out parseValue) || entries[j] == "");
                }
            }

            parseData();
        }

        void readFromExcel(string fileName)
        {
            int worksheetItter = 0;
            foreach (var worksheet in Workbook.Worksheets(fileName))
            {
                if (worksheetItter != 0)
                {
                    break;
                }

                // Retrieve column names
                for (int i = 0; true; ++i)
                {
                    // worksheet.Rows[0].Cells.Length provides an inconsistant length
                    // so this method of itteration condition is used
                    try
                    {
                        ds.Add(new DataEntry(worksheet.Rows.First().Cells[i].Text));
                    }
                    catch (IndexOutOfRangeException)
                    {
                        break;
                    }
                }

                // Fill column data
                bool first = true;
                foreach (var row in worksheet.Rows)
                {
                    if (first)
                    {
                        first = false;
                        continue;
                    }

                    int iter = 0;
                    foreach (var cell in row.Cells)
                    {
                        if (iter >= ds.Count)
                        {
                            break;
                        }

                        ds[iter].Data.Add(cell.Text == "" ? "[NONE]" : cell.Text);

                        int parseValue;
                        ds[iter].AllNumbers = ds[iter].AllNumbers && (Int32.TryParse(cell.Text, out parseValue) || cell.Text == "");
                        ++iter;
                    }
                }

                parseData();
                ++worksheetItter;
            }
        }

        void parseData()
        {
            for (int i = 0; i < ds.Count; ++i)
            {
                ds[i].UniquEntries = ds[i].Data.Distinct().ToList().Count;

                if (ds[i].AllNumbers)
                {
                    ds[i].NumberRange = new Tuple<double, double>(double.Parse(ds[i].Data.Min()), double.Parse(ds[i].Data.Max()));
                }
            }
        }
    }
}