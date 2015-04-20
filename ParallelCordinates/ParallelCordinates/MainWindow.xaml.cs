using System;
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
using System.IO;
using DataReader;

namespace ParallelCordinates
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private List<DataEntry> UserData;

        private void FileBrowserBtn(object sender, RoutedEventArgs e)
        {
            // Create OpenFileDialog 
            Microsoft.Win32.OpenFileDialog fileSelector = new Microsoft.Win32.OpenFileDialog();

            // Set filter for file extension and default file extension 
            fileSelector.DefaultExt = ".xlsx";
            fileSelector.Filter = "Excel Files (*.xlsx)|*.xlsx|Excel Files (*.xls)|*.xls";

            // Get the selected file name and display in a TextBox 
            if ((bool)fileSelector.ShowDialog())
            {
                try
                {
                    UserData = new ExcelReader(fileSelector.FileName).ds;
                    DataInterpretationBtn.IsEnabled = true;
                    FileNameLbl.Content = fileSelector.FileName.Substring(fileSelector.FileName.LastIndexOf("\\") + 1);
                }
                catch (IOException)
                {
                    FileNameLbl.Content = "Cannot open file (currently in use)";
                    DataInterpretationBtn.IsEnabled = false;
                    LaunchBtn.IsEnabled = false;
                }
            }
        }

        private void DisplayData(object sender, RoutedEventArgs e)
        {
            List<DataEntry> minimizedData = new List<DataEntry>();
            for (int i = 0; i < UserData.Count; ++i)
            {
                minimizedData.Add(UserData[i]);
                minimizedData[i].Data = minimizedData[i].Data.Take(21).ToList();
            }

            DataView page = new DataView(minimizedData);
            page.Show();
        }

        private void CheckBox_Checked(object sender, RoutedEventArgs e)
        {

        }
    }
}
