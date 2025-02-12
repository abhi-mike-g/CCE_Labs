namespace Calculator_Lab1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.Calculator = new System.Windows.Forms.GroupBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.Multiply = new System.Windows.Forms.Button();
            this.subtract = new System.Windows.Forms.Button();
            this.add = new System.Windows.Forms.Button();
            this.cmdSQRT = new System.Windows.Forms.Button();
            this.cmdFact = new System.Windows.Forms.Button();
            this.Divide = new System.Windows.Forms.Button();
            this.cmd8 = new System.Windows.Forms.Button();
            this.cmd9 = new System.Windows.Forms.Button();
            this.cmd7 = new System.Windows.Forms.Button();
            this.cmd6 = new System.Windows.Forms.Button();
            this.cmd5 = new System.Windows.Forms.Button();
            this.cmd4 = new System.Windows.Forms.Button();
            this.cmd2 = new System.Windows.Forms.Button();
            this.cmd3 = new System.Windows.Forms.Button();
            this.cmd1 = new System.Windows.Forms.Button();
            this.Ans = new System.Windows.Forms.Button();
            this.cmd0 = new System.Windows.Forms.Button();
            this.Calculator.SuspendLayout();
            this.SuspendLayout();
            // 
            // Calculator
            // 
            this.Calculator.Controls.Add(this.textBox1);
            this.Calculator.Controls.Add(this.Multiply);
            this.Calculator.Controls.Add(this.subtract);
            this.Calculator.Controls.Add(this.add);
            this.Calculator.Controls.Add(this.cmdSQRT);
            this.Calculator.Controls.Add(this.cmdFact);
            this.Calculator.Controls.Add(this.Divide);
            this.Calculator.Controls.Add(this.cmd8);
            this.Calculator.Controls.Add(this.cmd9);
            this.Calculator.Controls.Add(this.cmd7);
            this.Calculator.Controls.Add(this.cmd6);
            this.Calculator.Controls.Add(this.cmd5);
            this.Calculator.Controls.Add(this.cmd4);
            this.Calculator.Controls.Add(this.cmd2);
            this.Calculator.Controls.Add(this.cmd3);
            this.Calculator.Controls.Add(this.cmd1);
            this.Calculator.Controls.Add(this.Ans);
            this.Calculator.Controls.Add(this.cmd0);
            this.Calculator.Location = new System.Drawing.Point(12, 12);
            this.Calculator.Name = "Calculator";
            this.Calculator.Size = new System.Drawing.Size(199, 317);
            this.Calculator.TabIndex = 0;
            this.Calculator.TabStop = false;
            this.Calculator.Text = "Calculator";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(7, 37);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(114, 20);
            this.textBox1.TabIndex = 18;
            // 
            // Multiply
            // 
            this.Multiply.Location = new System.Drawing.Point(87, 141);
            this.Multiply.Name = "Multiply";
            this.Multiply.Size = new System.Drawing.Size(34, 23);
            this.Multiply.TabIndex = 17;
            this.Multiply.Text = "*";
            this.Multiply.UseVisualStyleBackColor = true;
            this.Multiply.Click += new System.EventHandler(this.Multiply_Click);
            // 
            // subtract
            // 
            this.subtract.Location = new System.Drawing.Point(47, 141);
            this.subtract.Name = "subtract";
            this.subtract.Size = new System.Drawing.Size(34, 23);
            this.subtract.TabIndex = 16;
            this.subtract.Text = "-";
            this.subtract.UseVisualStyleBackColor = true;
            this.subtract.Click += new System.EventHandler(this.subtract_Click);
            // 
            // add
            // 
            this.add.Location = new System.Drawing.Point(7, 141);
            this.add.Name = "add";
            this.add.Size = new System.Drawing.Size(34, 23);
            this.add.TabIndex = 15;
            this.add.Text = "+";
            this.add.UseVisualStyleBackColor = true;
            this.add.Click += new System.EventHandler(this.add_Click);
            // 
            // cmdSQRT
            // 
            this.cmdSQRT.Location = new System.Drawing.Point(87, 170);
            this.cmdSQRT.Name = "cmdSQRT";
            this.cmdSQRT.Size = new System.Drawing.Size(34, 23);
            this.cmdSQRT.TabIndex = 14;
            this.cmdSQRT.Text = "sqrt";
            this.cmdSQRT.UseVisualStyleBackColor = true;
            this.cmdSQRT.Click += new System.EventHandler(this.cmdSQRT_Click);
            // 
            // cmdFact
            // 
            this.cmdFact.Location = new System.Drawing.Point(47, 170);
            this.cmdFact.Name = "cmdFact";
            this.cmdFact.Size = new System.Drawing.Size(34, 23);
            this.cmdFact.TabIndex = 13;
            this.cmdFact.Text = "!";
            this.cmdFact.UseVisualStyleBackColor = true;
            this.cmdFact.Click += new System.EventHandler(this.cmdFact_Click);
            // 
            // Divide
            // 
            this.Divide.Location = new System.Drawing.Point(7, 170);
            this.Divide.Name = "Divide";
            this.Divide.Size = new System.Drawing.Size(34, 23);
            this.Divide.TabIndex = 12;
            this.Divide.Text = "/";
            this.Divide.UseVisualStyleBackColor = true;
            this.Divide.Click += new System.EventHandler(this.Divide_Click);
            // 
            // cmd8
            // 
            this.cmd8.Location = new System.Drawing.Point(47, 199);
            this.cmd8.Name = "cmd8";
            this.cmd8.Size = new System.Drawing.Size(34, 23);
            this.cmd8.TabIndex = 11;
            this.cmd8.Text = "8";
            this.cmd8.UseVisualStyleBackColor = true;
            this.cmd8.Click += new System.EventHandler(this.cmd8_Click);
            // 
            // cmd9
            // 
            this.cmd9.Location = new System.Drawing.Point(87, 199);
            this.cmd9.Name = "cmd9";
            this.cmd9.Size = new System.Drawing.Size(34, 23);
            this.cmd9.TabIndex = 10;
            this.cmd9.Text = "9";
            this.cmd9.UseVisualStyleBackColor = true;
            this.cmd9.Click += new System.EventHandler(this.cmd9_Click);
            // 
            // cmd7
            // 
            this.cmd7.Location = new System.Drawing.Point(7, 199);
            this.cmd7.Name = "cmd7";
            this.cmd7.Size = new System.Drawing.Size(34, 23);
            this.cmd7.TabIndex = 9;
            this.cmd7.Text = "7";
            this.cmd7.UseVisualStyleBackColor = true;
            this.cmd7.Click += new System.EventHandler(this.cmd7_Click);
            // 
            // cmd6
            // 
            this.cmd6.Location = new System.Drawing.Point(87, 228);
            this.cmd6.Name = "cmd6";
            this.cmd6.Size = new System.Drawing.Size(34, 23);
            this.cmd6.TabIndex = 8;
            this.cmd6.Text = "6";
            this.cmd6.UseVisualStyleBackColor = true;
            this.cmd6.Click += new System.EventHandler(this.cmd6_Click);
            // 
            // cmd5
            // 
            this.cmd5.Location = new System.Drawing.Point(47, 228);
            this.cmd5.Name = "cmd5";
            this.cmd5.Size = new System.Drawing.Size(34, 23);
            this.cmd5.TabIndex = 7;
            this.cmd5.Text = "5";
            this.cmd5.UseVisualStyleBackColor = true;
            this.cmd5.Click += new System.EventHandler(this.cmd5_Click);
            // 
            // cmd4
            // 
            this.cmd4.Location = new System.Drawing.Point(7, 228);
            this.cmd4.Name = "cmd4";
            this.cmd4.Size = new System.Drawing.Size(34, 23);
            this.cmd4.TabIndex = 6;
            this.cmd4.Text = "4";
            this.cmd4.UseVisualStyleBackColor = true;
            this.cmd4.Click += new System.EventHandler(this.cmd4_Click);
            // 
            // cmd2
            // 
            this.cmd2.Location = new System.Drawing.Point(47, 257);
            this.cmd2.Name = "cmd2";
            this.cmd2.Size = new System.Drawing.Size(34, 23);
            this.cmd2.TabIndex = 5;
            this.cmd2.Text = "2";
            this.cmd2.UseVisualStyleBackColor = true;
            this.cmd2.Click += new System.EventHandler(this.cmd2_Click);
            // 
            // cmd3
            // 
            this.cmd3.Location = new System.Drawing.Point(87, 257);
            this.cmd3.Name = "cmd3";
            this.cmd3.Size = new System.Drawing.Size(34, 23);
            this.cmd3.TabIndex = 4;
            this.cmd3.Text = "3";
            this.cmd3.UseVisualStyleBackColor = true;
            this.cmd3.Click += new System.EventHandler(this.cmd3_Click);
            // 
            // cmd1
            // 
            this.cmd1.Location = new System.Drawing.Point(7, 257);
            this.cmd1.Name = "cmd1";
            this.cmd1.Size = new System.Drawing.Size(34, 23);
            this.cmd1.TabIndex = 3;
            this.cmd1.Text = "1";
            this.cmd1.UseVisualStyleBackColor = true;
            this.cmd1.Click += new System.EventHandler(this.cmd1_Click);
            // 
            // Ans
            // 
            this.Ans.Location = new System.Drawing.Point(47, 286);
            this.Ans.Name = "Ans";
            this.Ans.Size = new System.Drawing.Size(74, 23);
            this.Ans.TabIndex = 2;
            this.Ans.Text = "=";
            this.Ans.UseVisualStyleBackColor = true;
            this.Ans.Click += new System.EventHandler(this.Ans_Click);
            // 
            // cmd0
            // 
            this.cmd0.Location = new System.Drawing.Point(7, 286);
            this.cmd0.Name = "cmd0";
            this.cmd0.Size = new System.Drawing.Size(34, 23);
            this.cmd0.TabIndex = 0;
            this.cmd0.Text = "0";
            this.cmd0.UseVisualStyleBackColor = true;
            this.cmd0.Click += new System.EventHandler(this.cmd0_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(321, 388);
            this.Controls.Add(this.Calculator);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Calculator.ResumeLayout(false);
            this.Calculator.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox Calculator;
        private System.Windows.Forms.Button Multiply;
        private System.Windows.Forms.Button subtract;
        private System.Windows.Forms.Button add;
        private System.Windows.Forms.Button cmdSQRT;
        private System.Windows.Forms.Button cmdFact;
        private System.Windows.Forms.Button Divide;
        private System.Windows.Forms.Button cmd8;
        private System.Windows.Forms.Button cmd9;
        private System.Windows.Forms.Button cmd7;
        private System.Windows.Forms.Button cmd6;
        private System.Windows.Forms.Button cmd5;
        private System.Windows.Forms.Button cmd4;
        private System.Windows.Forms.Button cmd2;
        private System.Windows.Forms.Button cmd3;
        private System.Windows.Forms.Button cmd1;
        private System.Windows.Forms.Button Ans;
        private System.Windows.Forms.Button cmd0;
        private System.Windows.Forms.TextBox textBox1;
    }
}

