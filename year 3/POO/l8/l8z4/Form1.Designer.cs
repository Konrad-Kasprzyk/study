namespace l8z4
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
            this.label1 = new System.Windows.Forms.Label();
            this.InsertCardButton = new System.Windows.Forms.Button();
            this.EjectCardButton = new System.Windows.Forms.Button();
            this.AcceptPinButton = new System.Windows.Forms.Button();
            this.EnterPinLabel = new System.Windows.Forms.Label();
            this.PinTextbox = new System.Windows.Forms.TextBox();
            this.ShowFundsButton = new System.Windows.Forms.Button();
            this.WithdrawFundsButton = new System.Windows.Forms.Button();
            this.AcceptWithdrawButton = new System.Windows.Forms.Button();
            this.EnterAmountLabel = new System.Windows.Forms.Label();
            this.CashInputTextBox = new System.Windows.Forms.TextBox();
            this.WithdrawErrorLabel = new System.Windows.Forms.Label();
            this.BackButton = new System.Windows.Forms.Button();
            this.ShowFundsLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(251, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(254, 31);
            this.label1.TabIndex = 0;
            this.label1.Text = "Witaj w bankomacie";
            // 
            // InsertCardButton
            // 
            this.InsertCardButton.Location = new System.Drawing.Point(257, 183);
            this.InsertCardButton.Name = "InsertCardButton";
            this.InsertCardButton.Size = new System.Drawing.Size(269, 52);
            this.InsertCardButton.TabIndex = 1;
            this.InsertCardButton.Text = "Włóż kartę";
            this.InsertCardButton.UseVisualStyleBackColor = true;
            this.InsertCardButton.Click += new System.EventHandler(this.InsertCard_Click);
            // 
            // EjectCardButton
            // 
            this.EjectCardButton.Location = new System.Drawing.Point(253, 328);
            this.EjectCardButton.Name = "EjectCardButton";
            this.EjectCardButton.Size = new System.Drawing.Size(269, 53);
            this.EjectCardButton.TabIndex = 2;
            this.EjectCardButton.Text = "Wyjmij kartę";
            this.EjectCardButton.UseVisualStyleBackColor = true;
            this.EjectCardButton.Visible = false;
            this.EjectCardButton.Click += new System.EventHandler(this.EjectCardButton_Click);
            // 
            // AcceptPinButton
            // 
            this.AcceptPinButton.Location = new System.Drawing.Point(257, 184);
            this.AcceptPinButton.Name = "AcceptPinButton";
            this.AcceptPinButton.Size = new System.Drawing.Size(269, 51);
            this.AcceptPinButton.TabIndex = 3;
            this.AcceptPinButton.Text = "Potwierdź";
            this.AcceptPinButton.UseVisualStyleBackColor = true;
            this.AcceptPinButton.Click += new System.EventHandler(this.AcceptPinButton_Click);
            // 
            // EnterPinLabel
            // 
            this.EnterPinLabel.AutoSize = true;
            this.EnterPinLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.EnterPinLabel.Location = new System.Drawing.Point(249, 80);
            this.EnterPinLabel.Name = "EnterPinLabel";
            this.EnterPinLabel.Size = new System.Drawing.Size(273, 20);
            this.EnterPinLabel.TabIndex = 4;
            this.EnterPinLabel.Text = "Wpisz pin i naciśnij przycisk Potwierdź";
            // 
            // PinTextbox
            // 
            this.PinTextbox.Location = new System.Drawing.Point(274, 128);
            this.PinTextbox.Name = "PinTextbox";
            this.PinTextbox.Size = new System.Drawing.Size(218, 20);
            this.PinTextbox.TabIndex = 5;
            this.PinTextbox.Text = "Dowolny napis jest dobrym pinem";
            // 
            // ShowFundsButton
            // 
            this.ShowFundsButton.Location = new System.Drawing.Point(257, 256);
            this.ShowFundsButton.Name = "ShowFundsButton";
            this.ShowFundsButton.Size = new System.Drawing.Size(269, 51);
            this.ShowFundsButton.TabIndex = 6;
            this.ShowFundsButton.Text = "Pokaż środki";
            this.ShowFundsButton.UseVisualStyleBackColor = true;
            this.ShowFundsButton.Click += new System.EventHandler(this.ShowFundsButton_Click);
            // 
            // WithdrawFundsButton
            // 
            this.WithdrawFundsButton.Location = new System.Drawing.Point(253, 183);
            this.WithdrawFundsButton.Name = "WithdrawFundsButton";
            this.WithdrawFundsButton.Size = new System.Drawing.Size(269, 51);
            this.WithdrawFundsButton.TabIndex = 7;
            this.WithdrawFundsButton.Text = "Wypłata";
            this.WithdrawFundsButton.UseVisualStyleBackColor = true;
            this.WithdrawFundsButton.Click += new System.EventHandler(this.WithdrawFundsButton_Click);
            // 
            // AcceptWithdrawButton
            // 
            this.AcceptWithdrawButton.Location = new System.Drawing.Point(253, 257);
            this.AcceptWithdrawButton.Name = "AcceptWithdrawButton";
            this.AcceptWithdrawButton.Size = new System.Drawing.Size(273, 50);
            this.AcceptWithdrawButton.TabIndex = 8;
            this.AcceptWithdrawButton.Text = "Wypłać";
            this.AcceptWithdrawButton.UseVisualStyleBackColor = true;
            this.AcceptWithdrawButton.Click += new System.EventHandler(this.AcceptWithdrawButton_Click);
            // 
            // EnterAmountLabel
            // 
            this.EnterAmountLabel.AutoSize = true;
            this.EnterAmountLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.EnterAmountLabel.Location = new System.Drawing.Point(316, 80);
            this.EnterAmountLabel.Name = "EnterAmountLabel";
            this.EnterAmountLabel.Size = new System.Drawing.Size(130, 20);
            this.EnterAmountLabel.TabIndex = 9;
            this.EnterAmountLabel.Text = "Wprowadź kwotę";
            // 
            // CashInputTextBox
            // 
            this.CashInputTextBox.Location = new System.Drawing.Point(274, 128);
            this.CashInputTextBox.Name = "CashInputTextBox";
            this.CashInputTextBox.Size = new System.Drawing.Size(218, 20);
            this.CashInputTextBox.TabIndex = 10;
            // 
            // WithdrawErrorLabel
            // 
            this.WithdrawErrorLabel.AutoSize = true;
            this.WithdrawErrorLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.WithdrawErrorLabel.Location = new System.Drawing.Point(49, 126);
            this.WithdrawErrorLabel.Name = "WithdrawErrorLabel";
            this.WithdrawErrorLabel.Size = new System.Drawing.Size(130, 20);
            this.WithdrawErrorLabel.TabIndex = 11;
            this.WithdrawErrorLabel.Text = "Za mało środków";
            // 
            // BackButton
            // 
            this.BackButton.Location = new System.Drawing.Point(253, 328);
            this.BackButton.Name = "BackButton";
            this.BackButton.Size = new System.Drawing.Size(269, 53);
            this.BackButton.TabIndex = 12;
            this.BackButton.Text = "Wróć";
            this.BackButton.UseVisualStyleBackColor = true;
            this.BackButton.Click += new System.EventHandler(this.BackButton_Click);
            // 
            // ShowFundsLabel
            // 
            this.ShowFundsLabel.AutoSize = true;
            this.ShowFundsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ShowFundsLabel.Location = new System.Drawing.Point(586, 126);
            this.ShowFundsLabel.Name = "ShowFundsLabel";
            this.ShowFundsLabel.Size = new System.Drawing.Size(125, 20);
            this.ShowFundsLabel.TabIndex = 13;
            this.ShowFundsLabel.Text = "Dostępne środki";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.ShowFundsLabel);
            this.Controls.Add(this.BackButton);
            this.Controls.Add(this.WithdrawErrorLabel);
            this.Controls.Add(this.CashInputTextBox);
            this.Controls.Add(this.EnterAmountLabel);
            this.Controls.Add(this.AcceptWithdrawButton);
            this.Controls.Add(this.WithdrawFundsButton);
            this.Controls.Add(this.ShowFundsButton);
            this.Controls.Add(this.PinTextbox);
            this.Controls.Add(this.EnterPinLabel);
            this.Controls.Add(this.AcceptPinButton);
            this.Controls.Add(this.EjectCardButton);
            this.Controls.Add(this.InsertCardButton);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button InsertCardButton;
        private System.Windows.Forms.Button EjectCardButton;
        private System.Windows.Forms.Button AcceptPinButton;
        private System.Windows.Forms.Label EnterPinLabel;
        private System.Windows.Forms.TextBox PinTextbox;
        private System.Windows.Forms.Button ShowFundsButton;
        private System.Windows.Forms.Button WithdrawFundsButton;
        private System.Windows.Forms.Button AcceptWithdrawButton;
        private System.Windows.Forms.Label EnterAmountLabel;
        private System.Windows.Forms.TextBox CashInputTextBox;
        private System.Windows.Forms.Label WithdrawErrorLabel;
        private System.Windows.Forms.Button BackButton;
        private System.Windows.Forms.Label ShowFundsLabel;
    }
}

