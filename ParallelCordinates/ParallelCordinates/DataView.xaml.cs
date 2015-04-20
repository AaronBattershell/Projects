﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using DataReader;
using System.Dynamic;

namespace ParallelCordinates
{
    public partial class DataView : Window
    {
        public DataView()
        {
            InitializeComponent();
        }

        public DataView(List<DataEntry> userData)
        {
            InitializeComponent();

            for (int i = 0; i < userData.Count; ++i)
            {
                DataGridTextColumn textColumn = new DataGridTextColumn();
                textColumn.Header = userData[i].ColumnName;
                textColumn.Binding = new Binding(userData[i].ColumnName.Replace(' ', '_'));
                ViewDataGrid.Columns.Add(textColumn);
            }

            for (int i = 0; i < userData[0].Data.Count; ++i)
            {
                dynamic row = new ExpandoObject();

                for (int j = 0; j < userData.Count; ++j)
                {
                    ((IDictionary<String, Object>)row)[userData[j].ColumnName.Replace(' ', '_')] = userData[j].Data[i];
                }

                ViewDataGrid.Items.Add(row);
            }
        }

        private void ViewDataGrid_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }
    }
}
