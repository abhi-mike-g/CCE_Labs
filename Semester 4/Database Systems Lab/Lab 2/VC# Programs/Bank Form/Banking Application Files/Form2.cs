using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Banking_Application
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void Crazy_SelectedIndexChanged(object sender, EventArgs e)
        {
            Box.Show.Overload("Deposit $100, \nWithdraw $50, \nTransfer to Beneficiary A: $200\n, Deposit $300, \nWithdraw $100");
        }
    }
}
