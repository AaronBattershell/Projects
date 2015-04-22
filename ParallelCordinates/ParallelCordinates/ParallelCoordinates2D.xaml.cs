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
        public ParallelCoordinates2D()
        {
            InitializeComponent();
        }

        public ParallelCoordinates2D(List<DataEntry> userData) 
        {
            InitializeComponent();
            //Measure(new Size(double.PositiveInfinity, double.PositiveInfinity));
            //Arrange(new Rect(0, 0, DesiredWidth, DesiredHeight));
            window.Measure(new Size(double.PositiveInfinity, double.PositiveInfinity));
            window.Arrange(new Rect(0, 0, window.window.DesiredSize.Width, window.window.DesiredSize.Height));


            for (int i = 0; i < userData.Count; ++i)
            {
                var a = new Line()
                {
                    X1 = i / (double)userData.Count * (window.ActualWidth + 0),
                    Y1 = 50,
                    X2 = i / (double)userData.Count * (window.ActualWidth + 0),
                    Y2 = (window.ActualHeight + 0) - 50,
                    StrokeThickness = 1,
                    Stroke = Brushes.Black
                };
                canvas.Children.Add(a);
                //dc.DrawLine(new Pen(Brushes.Black, 1), new Point(i / (double)userData.Count * width, 50), new Point(i / (double)userData.Count * width, height - 50));
            }

            var b = new Line()
            {
                X1 = 0,
                Y1 = 50,
                X2 = 2200,
                Y2 = (canvas.ActualHeight + 1080) - 50,
                StrokeThickness = 6,
                Stroke = Brushes.Red
            };
            canvas.Children.Add(b);

        }
    }

    class MyCanvas : Canvas
    {
        List<DataEntry> userData;

        public MyCanvas(List<DataEntry> userData) : base()
        {
            this.userData = userData;
        }

        protected override void OnRender(DrawingContext dc)
        {
            //drawRectangle(dc);
            //drawTriangle(dc);
            //drawLine(dc);

            double height = this.ActualHeight + 1080;
            double width = this.ActualWidth;

            for (int i = 0; i < userData.Count; ++i)
            {
                dc.DrawLine(new Pen(Brushes.Black, 1), new Point(i / (double)userData.Count * width, 50), new Point(i / (double)userData.Count * width, height - 50));
            }
        }

        void drawRectangle(DrawingContext dc)
        {
            dc.DrawRectangle(Brushes.Aqua, new Pen(Brushes.Black, 5), new Rect(new Point(100, 0), new Point(300, 100)));
        }

        void drawLine(DrawingContext dc)
        {
            dc.DrawLine(new Pen(Brushes.Black, 1), new Point(0, 100), new Point(100, 0));
        }

        void drawTriangle(DrawingContext dc)
        {
            PathFigure pathFigure = new PathFigure();
            pathFigure.StartPoint = new Point(100, 100);
            pathFigure.IsClosed = true;
            pathFigure.Segments.Add(new LineSegment(new Point(0, 200), true));
            pathFigure.Segments.Add(new LineSegment(new Point(200, 200), true));

            PathGeometry geometry = new PathGeometry();
            geometry.Figures.Add(pathFigure);

            dc.DrawGeometry(Brushes.Orange, new Pen(Brushes.Black, 5), geometry);
        }
    }
}
