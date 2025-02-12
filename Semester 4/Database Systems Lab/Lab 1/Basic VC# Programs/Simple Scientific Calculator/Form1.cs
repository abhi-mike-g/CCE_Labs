using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Calculator_Lab1
{
    public partial class Form1 : Form
    {
        string input = string.Empty; //to read the input when clicked
        string Op1 = string.Empty; //First operand
        string Op2 = string.Empty; //Second operand
        char Operator; //Operator
        double res = 0.0; //Final result
        public Form1()
        {
            InitializeComponent();
        }

        private void cmd0_Click(object sender, EventArgs e)
        {
            this.textBox1.Text = string.Empty;
            input = input + "0";
            this.textBox1.Text += input;

        }

        private void cmd1_Click(object sender, EventArgs e)
        {
            this.textBox1.Text = string.Empty;
            input = input + "1";
            this.textBox1.Text += input;
        }

        private void cmd2_Click(object sender, EventArgs e)
        {
            this.textBox1.Text = string.Empty;
            input = input + "2";
            this.textBox1.Text += input;
        }

        private void cmd3_Click(object sender, EventArgs e)
        {
            this.textBox1.Text = string.Empty;
            input = input + "3";
            this.textBox1.Text += input;
        }

        private void cmd4_Click(object sender, EventArgs e)
        {
            this.textBox1.Text = string.Empty;
            input = input + "4";
            this.textBox1.Text += input;
        }

        private void cmd5_Click(object sender, EventArgs e)
        {
            this.textBox1.Text = string.Empty;
            input = input + "5";
            this.textBox1.Text += input;
        }

        private void cmd6_Click(object sender, EventArgs e)
        {
            this.textBox1.Text = string.Empty;
            input = input + "6";
            this.textBox1.Text += input;
        }

        private void cmd7_Click(object sender, EventArgs e)
        {
            this.textBox1.Text = string.Empty;
            input = input + "7";
            this.textBox1.Text += input;
        }

        private void cmd8_Click(object sender, EventArgs e)
        {
            this.textBox1.Text = string.Empty;
            input = input + "8";
            this.textBox1.Text += input;
        }

        private void cmd9_Click(object sender, EventArgs e)
        {
            this.textBox1.Text = string.Empty;
            input = input + "9";
            this.textBox1.Text += input;
        }

        private void add_Click(object sender, EventArgs e)
        {
            Op1 = input;
            Operator = '+';
            input = string.Empty;
        }

        private void subtract_Click(object sender, EventArgs e)
        {
            Op1 = input;
            Operator = '-';
            input = string.Empty;
        }

        private void Multiply_Click(object sender, EventArgs e)
        {
            Op1 = input;
            Operator = '*';
            input = string.Empty;
        }

        private void Divide_Click(object sender, EventArgs e)
        {
            Op1 = input;
            Operator = '/';
            input = string.Empty;
        }

        private void Ans_Click(object sender, EventArgs e)
        {
            Op2 = input;
            double num1, num2;
            double.TryParse(Op1, out num1);
            double.TryParse(Op2, out num2);
            if (Operator == '+')
            {
                res = num1 + num2;
                this.textBox1.Text = res.ToString();
            }
            else if (Operator == '-')
            {
                res = num1 - num2;
                textBox1.Text = res.ToString();
            }
            else if (Operator == '*')
            {
                res = num1 * num2;
                textBox1.Text = res.ToString();
            }
            else if (Operator == '!')
            {
                int fact = 1;
                for (int i = 2; i <= num1; i++)
                    fact *= i;
                res = fact;
                textBox1.Text = res.ToString();
            }
            else if (Operator == '|')
            {
                res = Math.Sqrt(num1);
                textBox1.Text = res.ToString();
            }
            else if (Operator == '/')
            {
                if (num2 != 0)
                {
                    res = num1 / num2;
                    textBox1.Text = res.ToString();
                }
                else
                {
                    textBox1.Text = "DIV/Zero!";
                }
            }
            input = string.Empty;
        }

        private void cmdFact_Click(object sender, EventArgs e)
        {
            Op1 = input;
            Operator = '!';
            input = string.Empty;
        }

        private void cmdSQRT_Click(object sender, EventArgs e)
        {
            Op1 = input;
            Operator = '|';
            input = string.Empty;
        }
    }
}

// Below is the better and more modified version of the code, but it needs to be mapped to the buttons properly and the buttons need to be 
// named properly respectively
/*

    namespace Calculator_Lab1
{
    public partial class Form1 : Form
    {
        string input = string.Empty;
        string Op1 = string.Empty;
        string Op2 = string.Empty;
        char Operator;
        double res = 0.0;

        public Form1()
        {
            InitializeComponent();
        }

        private void Digit_Click(object sender, EventArgs e)
        {
            Button button = (Button)sender;
            input += button.Tag.ToString();
            textBox1.Text = input;
        }

        private void Operator_Click(object sender, EventArgs e)
        {
            Button button = (Button)sender;
            Op1 = input;
            Operator = button.Tag.ToString()[0];
            input = string.Empty;
        }

        private void Clear_Click(object sender, EventArgs e)
        {
            input = string.Empty;
            Op1 = string.Empty;
            Op2 = string.Empty;
            Operator = '\0';
            res = 0.0;
            textBox1.Text = string.Empty;
        }

        private void Ans_Click(object sender, EventArgs e)
        {
            Op2 = input;
            double num1, num2;
            double.TryParse(Op1, out num1);
            double.TryParse(Op2, out num2);

            switch (Operator)
            {
                case '+': res = num1 + num2; break;
                case '-': res = num1 - num2; break;
                case '*': res = num1 * num2; break;
                case '/':
                    res = num2 != 0 ? num1 / num2 : double.NaN;
                    textBox1.Text = num2 != 0 ? res.ToString() : "DIV/Zero!";
                    return;
                case '!':
                    if (num1 < 0) textBox1.Text = "Invalid Input!";
                    else
                    {
                        int fact = 1;
                        for (int i = 2; i <= num1; i++)
                            fact *= i;
                        res = fact;
                        textBox1.Text = res.ToString();
                    }
                    return;
                case '|':
                    if (num1 < 0) textBox1.Text = "Invalid Input!";
                    else
                    {
                        res = Math.Sqrt(num1);
                        textBox1.Text = res.ToString();
                    }
                    return;
                case 's':
                    res = Math.Sin(num1 * Math.PI / 180); // Convert degrees to radians
                    textBox1.Text = res.ToString();
                    return;
                case 'c':
                    res = Math.Cos(num1 * Math.PI / 180); // Convert degrees to radians
                    textBox1.Text = res.ToString();
                    return;
                case 't':
                    if (Math.Cos(num1 * Math.PI / 180) == 0)
                        textBox1.Text = "Undefined!";
                    else
                    {
                        res = Math.Tan(num1 * Math.PI / 180); // Convert degrees to radians
                        textBox1.Text = res.ToString();
                    }
                    return;
            }
            textBox1.Text = res.ToString();
        }
    }
}

*/