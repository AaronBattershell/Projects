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

        const double MIN_X_DISTANCE = 60;
        const double BORDER_DISTANCE = 50;
        const double NUMERIC_POINTS = 5;
        const double Y_COLUMN_OFFSET = - BORDER_DISTANCE / 2;
        const double TEXT_OFFSET_X = 3;
        const double TEXT_OFFSET_Y = - 25;


        DisplayData GraphData;

        public ParallelCoordinates2D()
        {
            InitializeComponent();
        }

        public ParallelCoordinates2D(List<DataEntry> userData) 
        {
            InitializeComponent();

            GraphData = new DisplayData();
            GraphData.GridData = userData.Where(e => e.UniquEntries <= 25 || e.AllNumbers == true).ToList();

            //MessageBoxResult messageBoxResult = System.Windows.MessageBox.Show("Good Columns: " + GraphData.Count(e => e.UniquEntries <= 25 || e.AllNumbers == true).ToString() + " of " + GraphData.Count().ToString(), "Alert", System.Windows.MessageBoxButton.OK);

            windowHeight = (int)SystemParameters.FullPrimaryScreenHeight;
            windowWidth = (int)SystemParameters.FullPrimaryScreenWidth;

            canvas.Height = windowHeight;
            canvas.Width = windowWidth;

            double normalWidth = (2 / (double)GraphData.GridData.Count * windowWidth) - (1 / (double)GraphData.GridData.Count * windowWidth);
            double XStep = Math.Max(normalWidth, MIN_X_DISTANCE);
            canvas.Width = XStep * GraphData.GridData.Count + BORDER_DISTANCE * 2;

            // Draw Vertical Lines
            for (int i = 0; i < GraphData.GridData.Count; ++i)
            {
                GraphData.ColumnPositions.Add(new ColumnData(new Point(XStep * i + XStep / 2 + BORDER_DISTANCE, BORDER_DISTANCE - Y_COLUMN_OFFSET), new Point(XStep * i + XStep / 2 + BORDER_DISTANCE, windowHeight - BORDER_DISTANCE - Y_COLUMN_OFFSET)));
                canvas.Children.Add(DrawLine(new Pen(Brushes.Red, 1), GraphData.ColumnPositions.Last().Top, GraphData.ColumnPositions.Last().Botumn));
                canvas.Children.Add(DrawText(GraphData.GridData[i].ColumnName, new Point(GraphData.ColumnPositions[i].Top.X - GraphData.GridData[i].ColumnName.Length * TEXT_OFFSET_X, -Y_COLUMN_OFFSET / 2 + (XStep < 150 ? (i % 3) * 20 : 0)), Colors.Black));
            }

            // Draw Horizontal Lines
            for (int i = 0; i < GraphData.GridData.Count; ++i)
            {
                if (GraphData.GridData[i].AllNumbers && GraphData.GridData[i].UniquEntries > 7)
                {
                    for (int j = 0; j < NUMERIC_POINTS; ++j)
                    {
                        double labelNumber = (j == 0 ? GraphData.GridData[i].NumberRange.First : j == NUMERIC_POINTS - 1 ? GraphData.GridData[i].NumberRange.Second : (GraphData.GridData[i].NumberRange.Second - GraphData.GridData[i].NumberRange.First) * (j / (double)NUMERIC_POINTS) + GraphData.GridData[i].NumberRange.First);

                        GraphData.ColumnPositions[i].YPlacements[j.ToString()] = (int)(j / NUMERIC_POINTS * (canvas.Height - 2 * BORDER_DISTANCE) + (0.5 / NUMERIC_POINTS * (canvas.Height - 2 * BORDER_DISTANCE)) + BORDER_DISTANCE - Y_COLUMN_OFFSET);
                        canvas.Children.Add(DrawLine(new Pen(Brushes.Black, 2), new Point(GraphData.ColumnPositions[i].Top.X - 10, GraphData.ColumnPositions[i].YPlacements[j.ToString()]), new Point(GraphData.ColumnPositions[i].Top.X + 10, GraphData.ColumnPositions[i].YPlacements[j.ToString()])));
                        canvas.Children.Add(DrawText(labelNumber.ToString(), new Point(GraphData.ColumnPositions[i].Top.X - labelNumber.ToString().Length * TEXT_OFFSET_X, GraphData.ColumnPositions[i].YPlacements[j.ToString()] + TEXT_OFFSET_Y), Colors.Black));
                    }
                }
                else
                {
                    List<string> uniquValues = GraphData.GridData[i].Data.Distinct().ToList();
                    for (int j = 0; j < uniquValues.Count; ++j)
                    {
                        GraphData.ColumnPositions[i].YPlacements[uniquValues[j]] = ((int)(j / (double)GraphData.GridData[i].UniquEntries * (canvas.Height - 2 * BORDER_DISTANCE) + (0.5 / (double)GraphData.GridData[i].UniquEntries * (canvas.Height - 2 * BORDER_DISTANCE)) + BORDER_DISTANCE - Y_COLUMN_OFFSET));
                        canvas.Children.Add(DrawLine(new Pen(Brushes.Black, 2), new Point(GraphData.ColumnPositions[i].Top.X - 10, GraphData.ColumnPositions[i].YPlacements[uniquValues[j]]), new Point(GraphData.ColumnPositions[i].Top.X + 10, GraphData.ColumnPositions[i].YPlacements[uniquValues[j]])));
                        canvas.Children.Add(DrawText(GraphData.GridData[i].Data[j], new Point(GraphData.ColumnPositions[i].Top.X - GraphData.GridData[i].Data[j].Length * TEXT_OFFSET_X, GraphData.ColumnPositions[i].YPlacements[uniquValues[j]] + TEXT_OFFSET_Y), Colors.Black));
                    }
                }
            }
        }

        public Line DrawLine(Pen p, Point p1, Point p2)
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

        public TextBlock DrawText(string text, Point location, Color color)
        {
            TextBlock t = new TextBlock()
            {
                Text = text,
                Foreground = new SolidColorBrush(color),
                Height = 30,
                Width = 200,
                Margin = new Thickness(location.X, location.Y, 0, 0)
            };

            return t;
        }
    }

    public class DisplayData
    {
        public DisplayData()
        {
            GridData = new List<DataEntry>();
            ColumnPositions = new List<ColumnData>();
        }

        public List<DataEntry> GridData { get; set; }
        public List<ColumnData> ColumnPositions { get; set; }
    }

    public class ColumnData
    {
        public ColumnData()
        {
            YPlacements = new Dictionary<string, int>();
        }

        public ColumnData(Point top, Point botumn) : this()
        {
            Top = top;
            Botumn = botumn;
        }

        public Point Top { get; set; }
        public Point Botumn { get; set; }
        public Dictionary<string, int> YPlacements { get; set; }
    }
}
