using System;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace FunctionGrapher.UI
{
    public partial class Form1 : Form
    {
        [DllImport("FunctionGrapher.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern double CalculateAt(string input, double xCoord);

        private string _expression = string.Empty;
        private readonly List<PointF> _points = new List<PointF>();

        private const int PointsCount = 100;
        private const int GridSteps = 20;

        public Form1()
        {
            InitializeComponent();
            ExpressionField.TextChanged += (sender, e) => _expression = ExpressionField.Text;
            DrawButton.Click += OnDrawButtonClicked;
            ErrorLabel.Visible = false;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            if (_points.Count == 0)
                return;

            var graphics = GraphPanel.CreateGraphics();
            graphics.Clear(Color.White);

            DrawGrid(graphics);
            DrawFunction(graphics);

            base.OnPaint(e);
        }

        private void OnDrawButtonClicked(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(_expression))
                return;

            ErrorLabel.Visible = false;
            _points.Clear();

            try
            {
                var axisLeft = -((float)GridSteps / 2);
                var axisRight = (float)GridSteps / 2;

                for (var index = 0; index < PointsCount; index++)
                {
                    var currentPos = (float) index;
                    var x = axisLeft + (axisRight - axisLeft) * ((currentPos - 0) / ((float)PointsCount - 0));
                    var result = CalculateAt(_expression, x);
                    _points.Add(new PointF(x, (float)result));
                }
            }
            catch
            {
                ErrorLabel.Visible = true;
            }

            Invalidate();
        }

        private void DrawGrid(Graphics graphics)
        {
            // Horizontal
            graphics.DrawLine(Pens.Black, 0, GraphPanel.Height / 2, GraphPanel.Width, GraphPanel.Height / 2);

            var numberingOffsetY = GraphPanel.Height / GridSteps;
            for (var index = 0; index < GridSteps; index++)
            {
                var posX = GraphPanel.Width / 2;
                var posY = numberingOffsetY * index;
                var marking = (~(index - GridSteps / 2 - 1)).ToString();
                graphics.DrawString(marking, DefaultFont, Brushes.Black, posX, posY);
            }

            // Vertical
            graphics.DrawLine(Pens.Black, GraphPanel.Width / 2, 0 , GraphPanel.Width / 2, GraphPanel.Height);

            var numberingOffsetX = GraphPanel.Width / GridSteps;
            for (int index = 0; index < GridSteps; index++)
            {
                var posX = index * numberingOffsetX;
                var posY = GraphPanel.Height / 2;
                var marking = (~(index - GridSteps / 2 - 1)).ToString();
                if(marking != "0")
                    graphics.DrawString(marking, DefaultFont, Brushes.Black, posX, posY);
            }
        }

        private void DrawFunction(Graphics graphics)
        {
            var axisLeft = -((float)GridSteps / 2);
            var axisRight = (float)GridSteps / 2;
            var screenLeftX = (float)0;
            var screenRightX = (float)GraphPanel.Width;
            var screenLeftY = (float)0;
            var screenRightY = (float)GraphPanel.Height;

            var newPoints = new List<PointF>(_points.Count);

            foreach (var point in _points)
            {
                var x = screenLeftX + (screenRightX - screenLeftX) * ((point.X - axisLeft) / (axisRight - axisLeft));
                var y = screenLeftY + (screenRightY - screenLeftY) * ((-point.Y - axisLeft) / (axisRight - axisLeft));
                newPoints.Add(new PointF(x, y));
            }

            graphics.DrawLines(Pens.Black, newPoints.ToArray());
        }
    }
}
