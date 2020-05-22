using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace l8z4
{
    public partial class Form1 : Form
    {
        CashMachine cashMachine = new CashMachine();
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            hideAllControls();
            InsertCardButton.Visible = true;
        }

        private void hideAllControls()
        {
            EnterPinLabel.Visible = false;
            PinTextbox.Visible = false;
            AcceptPinButton.Visible = false;
            InsertCardButton.Visible = false;
            EjectCardButton.Visible = false;
            WithdrawFundsButton.Visible = false;
            ShowFundsButton.Visible = false;
            CashInputTextBox.Visible = false;
            EnterAmountLabel.Visible = false;
            AcceptWithdrawButton.Visible = false;
            WithdrawErrorLabel.Visible = false;
            BackButton.Visible = false;
            ShowFundsLabel.Visible = false;
            CashInputTextBox.Text = "";
            WithdrawErrorLabel.Text = "";
            PinTextbox.Text = "Dowolny napis jest dobrym pinem";
        }

        private void InsertCard_Click(object sender, EventArgs e)
        {
            hideAllControls();
            EnterPinLabel.Visible = true;
            PinTextbox.Visible = true;
            AcceptPinButton.Visible = true;
            EjectCardButton.Visible = true;
            cashMachine.EnterCard();

        }

        private void EjectCardButton_Click(object sender, EventArgs e)
        {
            hideAllControls();
            InsertCardButton.Visible = true;
            cashMachine.EjectCard();
        }

        private void AcceptPinButton_Click(object sender, EventArgs e)
        {
            hideAllControls();
            ShowFundsButton.Visible = true;
            EjectCardButton.Visible = true;
            ShowFundsButton.Visible = true;
            WithdrawFundsButton.Visible = true;
            cashMachine.EnterPin();
        }

        private void WithdrawFundsButton_Click(object sender, EventArgs e)
        {
            hideAllControls();
            EnterAmountLabel.Visible = true;
            CashInputTextBox.Visible = true;
            AcceptWithdrawButton.Visible = true;
            BackButton.Visible = true;
            WithdrawErrorLabel.Visible = true;
            ShowFundsLabel.Visible = true;
            ShowFundsLabel.Text = "Dostępne środki: ";
            ShowFundsLabel.Text += cashMachine.ShowFunds().ToString();
        }

        private void AcceptWithdrawButton_Click(object sender, EventArgs e)
        {
            int funds;
            if (!int.TryParse(CashInputTextBox.Text, out funds))
            {
                WithdrawErrorLabel.Text = "Błąd. Wprowadź liczbę";
                return;
            }   
            try
            {
                cashMachine.WithdrawFunds(funds);
                ShowFundsLabel.Text = "Dostępne środki: ";
                ShowFundsLabel.Text += cashMachine.ShowFunds().ToString();
            }
            catch(Exception err)
            {
                WithdrawErrorLabel.Text = err.Message;
            }
        }

        private void BackButton_Click(object sender, EventArgs e)
        {
            hideAllControls();
            ShowFundsButton.Visible = true;
            EjectCardButton.Visible = true;
            ShowFundsButton.Visible = true;
            WithdrawFundsButton.Visible = true;
        }

        private void ShowFundsButton_Click(object sender, EventArgs e)
        {
            hideAllControls();
            BackButton.Visible = true;
            ShowFundsLabel.Visible = true;
            ShowFundsLabel.Text = "Dostępne środki: ";
            ShowFundsLabel.Text += cashMachine.ShowFunds().ToString();
        }
    }

    public class CashMachine : IState
    {
        public IState state;
        public int funds = 100;

        public CashMachine()
        {
            this.state = new CardNotEnteredState(this);
        }

        public void EjectCard()
        {
            this.state.EjectCard();
        }

        public void EnterCard()
        {
            this.state.EnterCard();
        }

        public void EnterPin()
        {
            this.state.EnterPin();
        }

        public int ShowFunds()
        {
            return this.state.ShowFunds();
        }

        public void WithdrawFunds(int funds)
        {
            this.state.WithdrawFunds(funds);
        }
    }

    public interface IState
    {
        void EnterCard();
        void EnterPin();
        int ShowFunds();
        void WithdrawFunds(int funds);
        void EjectCard();
    }

    public class CardEnteredPinEnteredState : IState
    {
        private CashMachine cashMachine;

        public CardEnteredPinEnteredState(CashMachine cashMachine)
        {
            this.cashMachine = cashMachine;
        }

        public void EjectCard()
        {
            this.cashMachine.state = new CardNotEnteredState(this.cashMachine);
        }

        public void EnterCard()
        {
            throw new InvalidOperationException();
        }

        public void EnterPin()
        {
            throw new InvalidOperationException();
        }

        public int ShowFunds()
        {
            return this.cashMachine.funds;
        }

        public void WithdrawFunds(int funds)
        {
            if (this.cashMachine.funds < funds)
            {
                throw new Exception("Niewystarczająca ilość środków");
            }
            this.cashMachine.funds -= funds;
        }
    }

    public class CardEnteredNoPinEnteredState : IState
    {
        private CashMachine cashMachine;

        public CardEnteredNoPinEnteredState(CashMachine cashMachine)
        {
            this.cashMachine = cashMachine;
        }

        public void EjectCard()
        {
            this.cashMachine.state = new CardNotEnteredState(this.cashMachine);
        }

        public void EnterCard()
        {
            throw new InvalidOperationException();
        }

        public void EnterPin()
        {
            this.cashMachine.state = new CardEnteredPinEnteredState(this.cashMachine);
        }

        public int ShowFunds()
        {
            throw new InvalidOperationException();
        }

        public void WithdrawFunds(int funds)
        {
            throw new InvalidOperationException();
        }
    }

    public class CardNotEnteredState : IState
    {
        private CashMachine cashMachine;

        public CardNotEnteredState(CashMachine cashMachine)
        {
            this.cashMachine = cashMachine;
        }

        public void EjectCard()
        {
            throw new InvalidOperationException();
        }

        public void EnterCard()
        {
            this.cashMachine.state = new CardEnteredNoPinEnteredState(this.cashMachine);
        }

        public void EnterPin()
        {
            throw new InvalidOperationException();
        }

        public int ShowFunds()
        {
            throw new InvalidOperationException();
        }

        public void WithdrawFunds(int funds)
        {
            throw new InvalidOperationException();
        }
    }
}
