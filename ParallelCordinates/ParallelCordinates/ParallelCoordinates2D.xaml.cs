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
using System.Windows.Shapes;
using System.IO;
using DataReader;

namespace ParallelCordinates
{
    public partial class ParallelCoordinates2D : Window
    {
        int windowHeight;
        int windowWidth;

        const double MIN_DISTANCE = 60;

        List<DataEntry> GraphData;

        public ParallelCoordinates2D()
        {
            InitializeComponent();
        }

        public ParallelCoordinates2D(List<DataEntry> userData) 
        {
            InitializeComponent();

            GraphData = userData;

            //MessageBoxResult messageBoxResult = System.Windows.MessageBox.Show("Good Columns: " + GraphData.Count(e => e.UniquEntries <= 25 || e.AllNumbers == true).ToString() + " of " + GraphData.Count().ToString(), "Alert", System.Windows.MessageBoxButton.OK);

            windowHeight = (int)SystemParameters.FullPrimaryScreenHeight;
            windowWidth = (int)SystemParameters.FullPrimaryScreenWidth;

            canvas.Height = windowHeight;
            canvas.Width = windowWidth;

            double normalWidth = (2 / (double)userData.Count * windowWidth) - (1 / (double)userData.Count * windowWidth);

            double XStep = Math.Max(normalWidth, MIN_DISTANCE);

            canvas.Width = XStep * userData.Count;

            for (int i = 0; i < userData.Count; ++i)
            {
                canvas.Children.Add(DrawLine(new Pen(Brushes.Red, 1), new Point(XStep * i + XStep / 2, 50), new Point(XStep * i + XStep / 2, windowHeight - 50)));
            }
        }

        Line DrawLine(Pen p, Point p1, Point p2)
        {
            Line l = new Line()
            {
                X1 = p1.X,
                Y1 = p1.Y,
                X2 = p2.X,
                Y2 = p2.Y,
                StrokeThickness = p.Thickness,
                Stroke = p.Brush
            };

            return l;
        }
    }
}
