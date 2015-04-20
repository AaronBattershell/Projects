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
        public DataEntry()
        {

        }

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

            foreach (var worksheet in Workbook.Worksheets(fileName))
            {
                // Retrieve column names
                for (int i = 0; true /*i < worksheet.Rows[0].Cells.Length*/; ++i)
                {
                    // worksheet.Rows[0].Cells.Length provides an inconsitance length
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

                        ds[iter].Data.Add(cell.Text);

                        int parseValue;
                        ds[iter].AllNumbers = ds[iter].AllNumbers && Int32.TryParse(cell.Text, out parseValue);
                        ++iter;
                    }
                }

                // Sort through data
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
}