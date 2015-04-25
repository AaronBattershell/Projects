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
    public partial class MainWindow : Window
    {
        private List<DataEntry> UserData;
        string VisualizationMethod;

        private void FileBrowserBtn(object sender, RoutedEventArgs e)
        {
            // Create OpenFileDialog 
            Microsoft.Win32.OpenFileDialog fileSelector = new Microsoft.Win32.OpenFileDialog();

            // Set filter for file extension and default file extension 
            fileSelector.DefaultExt = ".xlsx";
            fileSelector.Filter = "Excel Files (*.xlsx)|*.xlsx|Excel Files (*.xls)|*.xls|Text Files (*.txt)|*.txt|All File Types (*.*)|*.*";

            // Get the selected file name and display in a TextBox 
            if ((bool)fileSelector.ShowDialog())
            {
                try
                {
                    UserData = new ExcelReader(fileSelector.FileName).ds;
                    DataInterpretationBtn.IsEnabled = true;
                    LaunchBtn.IsEnabled = true;
                    FileNameLbl.Content = fileSelector.FileName.Substring(fileSelector.FileName.LastIndexOf("\\") + 1);
                }
                catch (IOException)
                {
                    FileNameLbl.Content = "Cannot open file (currently in use)";
                    DataInterpretationBtn.IsEnabled = false;
                    LaunchBtn.IsEnabled = false;
                }
                /*catch
                {
                    FileNameLbl.Content = "Error parsing data";
                    DataInterpretationBtn.IsEnabled = false;
                    LaunchBtn.IsEnabled = false;
                }*/
            }
        }

        private void DisplayData(object sender, RoutedEventArgs e)
        {
            List<DataEntry> minimizedData = new List<DataEntry>();
            for (int i = 0; i < UserData.Count; ++i)
            {

                minimizedData.Add(new DataEntry(UserData[i].ColumnName));
                for (int j = 0; j < 21 && j < UserData[i].Data.Count; ++j)
                {
                    minimizedData[i].Data.Add(UserData[i].Data[j]);
                }
            }

            DataView page = new DataView(minimizedData);
            
            if (!page.BrokenView)
            {
                page.Show();
            }
        }

        private void CheckBox_Checked(object sender, RoutedEventArgs e)
        {
            var visualizationRadioBtn = (RadioButton)sender;
            VisualizationMethod = (string)visualizationRadioBtn.Content;
        }

        private void LaunchBtn_Click(object sender, RoutedEventArgs e)
        {
            if (VisualizationMethod == "2D in 2D")
            {
                ParallelCoordinates2D page = new ParallelCoordinates2D(UserData);
                page.Show();
            }
            else if (VisualizationMethod == "2D in 3D Spiral")
            {
                FileNameLbl.Content = "Thing 3";
            }
        }
    }
}
