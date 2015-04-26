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
        double CalculatedXStep;

        const double MIN_X_STEP = 300;
        const double BORDER_DISTANCE = 50;
        const double NUMERIC_POINTS = 5;
        const double START_APPROXIMATION = 10;
        const double Y_COLUMN_OFFSET = - BORDER_DISTANCE / 2;
        const double TEXT_OFFSET_X = 3;
        const double TEXT_OFFSET_Y = - 25;
        const string EMPTY_FIELD = "[Not Available]";

        int DownMouseColumnIndex = -1;
        int UpMouseColumnIndex = -1;

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

            canvas.Height = (int)SystemParameters.FullPrimaryScreenHeight;
            canvas.Width = (int)SystemParameters.FullPrimaryScreenWidth;

            //double normalWidth = (2 / (double)GraphData.GridData.Count * canvas.Width) - (1 / (double)GraphData.GridData.Count * canvas.Height);
            double normalWidth = (canvas.Width - BORDER_DISTANCE * 2) / GraphData.GridData.Count;
            
            CalculatedXStep = Math.Max(normalWidth, MIN_X_STEP);
            canvas.Width = CalculatedXStep * GraphData.GridData.Count + BORDER_DISTANCE * 2;

            // Draw Vertical Lines
            for (int i = 0; i < GraphData.GridData.Count; ++i)
            {
                GraphData.ColumnPositions.Add(new ColumnData(new Point(CalculatedXStep * i + CalculatedXStep / 2 + BORDER_DISTANCE, BORDER_DISTANCE - Y_COLUMN_OFFSET), new Point(CalculatedXStep * i + CalculatedXStep / 2 + BORDER_DISTANCE, canvas.Height - BORDER_DISTANCE - Y_COLUMN_OFFSET)));
            }

            // Draw Horizontal Lines
            for (int i = 0; i < GraphData.GridData.Count; ++i)
            {
                if (GraphData.GridData[i].AllNumbers && GraphData.GridData[i].UniquEntries > START_APPROXIMATION)
                {
                    for (int j = 0; j < NUMERIC_POINTS; ++j)
                    {
                        double labelNumber = (j == 0 ? GraphData.GridData[i].NumberRange.First : (j == NUMERIC_POINTS - 1 ? GraphData.GridData[i].NumberRange.Second : (GraphData.GridData[i].NumberRange.Second - GraphData.GridData[i].NumberRange.First) * (j / (double)NUMERIC_POINTS) + GraphData.GridData[i].NumberRange.First));

                        GraphData.ColumnPositions[i].YPlacements[labelNumber.ToString()] = (int)(j / (NUMERIC_POINTS + (GraphData.GridData[i].ContainsEmptyEntry ? 1 : 0)) * (canvas.Height - 2 * BORDER_DISTANCE) + (0.5 / (NUMERIC_POINTS + (GraphData.GridData[i].ContainsEmptyEntry ? 1 : 0)) * (canvas.Height - 2 * BORDER_DISTANCE)) + BORDER_DISTANCE - Y_COLUMN_OFFSET);
                    }

                    if (GraphData.GridData[i].ContainsEmptyEntry)
                    {
                        GraphData.ColumnPositions[i].YPlacements[EMPTY_FIELD] = (int)((NUMERIC_POINTS) / (NUMERIC_POINTS + (GraphData.GridData[i].ContainsEmptyEntry ? 1 : 0)) * (canvas.Height - 2 * BORDER_DISTANCE) + (0.5 / (NUMERIC_POINTS + (GraphData.GridData[i].ContainsEmptyEntry ? 1 : 0)) * (canvas.Height - 2 * BORDER_DISTANCE)) + BORDER_DISTANCE - Y_COLUMN_OFFSET);
                    }
                }
                else
                {
                    var uniquValues = GraphData.GridData[i].Data.Distinct().Where(e => e[0] != '[').ToList();

                    sortList(uniquValues, GraphData.GridData[i].AllNumbers);

                    if (GraphData.GridData[i].ContainsEmptyEntry)
                    {
                        uniquValues.Add(EMPTY_FIELD);
                    }

                    for (int j = 0; j < uniquValues.Count; ++j)
                    {
                        GraphData.ColumnPositions[i].YPlacements[uniquValues[j]] = ((int)(j / (double)GraphData.GridData[i].UniquEntries * (canvas.Height - 2 * BORDER_DISTANCE) + (0.5 / (double)GraphData.GridData[i].UniquEntries * (canvas.Height - 2 * BORDER_DISTANCE)) + BORDER_DISTANCE - Y_COLUMN_OFFSET));
                    }
                }
            }

            drawScreen();
        }

        public void sortList(List<string> values, bool isNumbers = false)
        {
            if (!isNumbers)
            {
                values.Sort();
            }
            else
            {
                List<double> newValues = new List<double>();
                foreach (var val in values)
                {
                    newValues.Add(double.Parse(val));
                }

                newValues.Sort();

                values = new List<string>();

                foreach (var val in newValues)
                {
                    values.Add(val.ToString());
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

        private void mouseDown(object sender, RoutedEventArgs e)
        {
            //Point p = Mouse.GetPosition(canvas);
            //MessageBoxResult messageBoxResult = System.Windows.MessageBox.Show("Down at column: " + GraphData.GridData[getColumn(p)].ColumnName, "Alert", System.Windows.MessageBoxButton.OK);
         
            UpMouseColumnIndex = getColumn(Mouse.GetPosition(canvas));
        }

        private void mouseUP(object sender, RoutedEventArgs e)
        {
            //Point p = Mouse.GetPosition(canvas);
            //MessageBoxResult messageBoxResult = System.Windows.MessageBox.Show("Up at column: " + GraphData.GridData[getColumn(p)].ColumnName, "Alert", System.Windows.MessageBoxButton.OK);


            DownMouseColumnIndex = getColumn(Mouse.GetPosition(canvas));

            if (UpMouseColumnIndex != -1 && UpMouseColumnIndex != -1 && DownMouseColumnIndex != UpMouseColumnIndex)
            {
                // switch indicies
            }

            UpMouseColumnIndex = -1;
        }

        public int getColumn(Point p)
        {
            for (int i = 0; i < GraphData.GridData.Count - 1; ++i)
            {
                double halfWidth = CalculatedXStep / 2;

                if (GraphData.ColumnPositions[i].Top.X - halfWidth < p.X && p.X < GraphData.ColumnPositions[i].Top.X + halfWidth)
                {
                    return i;
                }
            }

            return -1;
        }

        void drawScreen()
        {
            canvas.Children.Clear();

            drawColumns();
            drawDatasetLines();
            drawColumnDataPoints();
        }

        void drawColumns()
        {
            for (int i = 0; i < GraphData.GridData.Count; ++i)
            {
                canvas.Children.Add(DrawLine(new Pen(Brushes.DarkSalmon, 1), GraphData.ColumnPositions[i].Top, GraphData.ColumnPositions[i].Botumn));
                canvas.Children.Add(DrawText(GraphData.GridData[i].ColumnName, new Point(GraphData.ColumnPositions[i].Top.X - GraphData.GridData[i].ColumnName.Length * TEXT_OFFSET_X, -Y_COLUMN_OFFSET / 2 + (CalculatedXStep < 150 ? (i % 3) * 20 : 0)), Colors.Black));
            }
        }

        void drawColumnDataPoints()
        {
            for (int i = 0; i < GraphData.GridData.Count; ++i)
            {
                if (GraphData.GridData[i].AllNumbers && GraphData.GridData[i].UniquEntries > START_APPROXIMATION)
                {
                    for (int j = 0; j < NUMERIC_POINTS; ++j)
                    {
                        double labelNumber = (j == 0 ? GraphData.GridData[i].NumberRange.First : (j == NUMERIC_POINTS - 1 ? GraphData.GridData[i].NumberRange.Second : (GraphData.GridData[i].NumberRange.Second - GraphData.GridData[i].NumberRange.First) * (j / (double)NUMERIC_POINTS) + GraphData.GridData[i].NumberRange.First));

                        canvas.Children.Add(DrawLine(new Pen(Brushes.Black, 2), new Point(GraphData.ColumnPositions[i].Top.X - 10, GraphData.ColumnPositions[i].YPlacements[labelNumber.ToString()]), new Point(GraphData.ColumnPositions[i].Top.X + 10, GraphData.ColumnPositions[i].YPlacements[labelNumber.ToString()])));
                        canvas.Children.Add(DrawText(labelNumber.ToString(), new Point(GraphData.ColumnPositions[i].Top.X - labelNumber.ToString().Length * TEXT_OFFSET_X, GraphData.ColumnPositions[i].YPlacements[labelNumber.ToString()] + TEXT_OFFSET_Y), Colors.Black));
                    }

                    if (GraphData.GridData[i].ContainsEmptyEntry)
                    {
                        canvas.Children.Add(DrawLine(new Pen(Brushes.Black, 2), new Point(GraphData.ColumnPositions[i].Top.X - 10, GraphData.ColumnPositions[i].YPlacements[EMPTY_FIELD]), new Point(GraphData.ColumnPositions[i].Top.X + 10, GraphData.ColumnPositions[i].YPlacements[EMPTY_FIELD])));
                        canvas.Children.Add(DrawText(EMPTY_FIELD, new Point(GraphData.ColumnPositions[i].Top.X - EMPTY_FIELD.ToString().Length * TEXT_OFFSET_X, GraphData.ColumnPositions[i].YPlacements[EMPTY_FIELD] + TEXT_OFFSET_Y), Colors.Black));
                    }
                }
                else
                {
                    var uniquValues = GraphData.GridData[i].Data.Distinct().Where(e => e[0] != '[').ToList();

                    for (int j = 0; j < uniquValues.Count; ++j)
                    {
                        canvas.Children.Add(DrawLine(new Pen(Brushes.Black, 2), new Point(GraphData.ColumnPositions[i].Top.X - 10, GraphData.ColumnPositions[i].YPlacements[uniquValues[j]]), new Point(GraphData.ColumnPositions[i].Top.X + 10, GraphData.ColumnPositions[i].YPlacements[uniquValues[j]])));
                        canvas.Children.Add(DrawText(uniquValues[j], new Point(GraphData.ColumnPositions[i].Top.X - uniquValues[j].Length * TEXT_OFFSET_X, GraphData.ColumnPositions[i].YPlacements[uniquValues[j]] + TEXT_OFFSET_Y), Colors.Black));
                    }
                }
            }
        }

        void drawDatasetLines()
        {
            for (int i = 0; i < GraphData.GridData[0].Data.Count; ++i)
            {
                Point left = getDataPointCoordinates(i, 0);;
                Point right;

                for (int j = 1; j < GraphData.GridData.Count; ++j)
                {
                    right = getDataPointCoordinates(i, j);

                    canvas.Children.Add(DrawLine(new Pen(Brushes.Gray, .5), left, right));
                    left = right;
                }
            }
        }

        Point getDataPointCoordinates(int i, int j)
        {
            // Case: Too many numeric points, so approximation must take place
            if (GraphData.GridData[j].AllNumbers && GraphData.GridData[j].UniquEntries > START_APPROXIMATION)
            {
                //  Case: No avalid entry provided
                if (GraphData.GridData[j].Data[i][0] == '[')
                {
                    return new Point(GraphData.ColumnPositions[j].Top.X, GraphData.ColumnPositions[j].YPlacements[EMPTY_FIELD]);
                }
                else // Case: Approximate location of numeric point
                {
                    // Point location based on range extreem values
                    double range = (GraphData.GridData[j].NumberRange.Second - GraphData.GridData[j].NumberRange.First);
                    double currentValue = Double.Parse(GraphData.GridData[j].Data[i]);
                    double heightPercentage = (currentValue - GraphData.GridData[j].NumberRange.First) / range;
                    double heightDistance = GraphData.ColumnPositions[j].YPlacements[GraphData.GridData[j].NumberRange.Second.ToString()] - GraphData.ColumnPositions[j].YPlacements[GraphData.GridData[j].NumberRange.First.ToString()];
                    double YVal = heightPercentage * heightDistance + GraphData.ColumnPositions[j].YPlacements[GraphData.GridData[j].NumberRange.First.ToString()];
                    return new Point(GraphData.ColumnPositions[j].Top.X, YVal);
                }
            }
            else // Case: No approximations needed 
            {
                string currentField = (GraphData.GridData[j].Data[i][0] == '[' ? EMPTY_FIELD : GraphData.GridData[j].Data[i]);
                return new Point(GraphData.ColumnPositions[j].Top.X, GraphData.ColumnPositions[j].YPlacements[currentField]);
            }
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
