namespace l7z1
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
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.NodePanel = new System.Windows.Forms.Panel();
            this.NodePanelListView = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.NodePanelButton = new System.Windows.Forms.Button();
            this.LeafPanel = new System.Windows.Forms.Panel();
            this.LeafPanelListView = new System.Windows.Forms.ListView();
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader5 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader6 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.LeafPanelButton = new System.Windows.Forms.Button();
            this.NodePanel.SuspendLayout();
            this.LeafPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // treeView1
            // 
            this.treeView1.Location = new System.Drawing.Point(12, 12);
            this.treeView1.Name = "treeView1";
            this.treeView1.Size = new System.Drawing.Size(142, 426);
            this.treeView1.TabIndex = 1;
            this.treeView1.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeView1_AfterSelect);
            // 
            // NodePanel
            // 
            this.NodePanel.Controls.Add(this.NodePanelListView);
            this.NodePanel.Controls.Add(this.NodePanelButton);
            this.NodePanel.Location = new System.Drawing.Point(160, 12);
            this.NodePanel.Name = "NodePanel";
            this.NodePanel.Size = new System.Drawing.Size(688, 426);
            this.NodePanel.TabIndex = 2;
            this.NodePanel.Visible = false;
            // 
            // NodePanelListView
            // 
            this.NodePanelListView.Alignment = System.Windows.Forms.ListViewAlignment.Left;
            this.NodePanelListView.BackColor = System.Drawing.SystemColors.Window;
            this.NodePanelListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2});
            this.NodePanelListView.ForeColor = System.Drawing.SystemColors.WindowText;
            this.NodePanelListView.FullRowSelect = true;
            this.NodePanelListView.GridLines = true;
            this.NodePanelListView.HideSelection = false;
            this.NodePanelListView.Location = new System.Drawing.Point(3, 45);
            this.NodePanelListView.Name = "NodePanelListView";
            this.NodePanelListView.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.NodePanelListView.Size = new System.Drawing.Size(387, 378);
            this.NodePanelListView.TabIndex = 1;
            this.NodePanelListView.UseCompatibleStateImageBehavior = false;
            this.NodePanelListView.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "Imie";
            this.columnHeader1.Width = 169;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Nazwisko";
            this.columnHeader2.Width = 256;
            // 
            // NodePanelButton
            // 
            this.NodePanelButton.Location = new System.Drawing.Point(3, 3);
            this.NodePanelButton.Name = "NodePanelButton";
            this.NodePanelButton.Size = new System.Drawing.Size(126, 36);
            this.NodePanelButton.TabIndex = 0;
            this.NodePanelButton.Text = "Dodaj Użytkownika";
            this.NodePanelButton.UseVisualStyleBackColor = true;
            this.NodePanelButton.Click += new System.EventHandler(this.NodePanelButton_Click);
            // 
            // LeafPanel
            // 
            this.LeafPanel.Controls.Add(this.LeafPanelListView);
            this.LeafPanel.Controls.Add(this.LeafPanelButton);
            this.LeafPanel.Location = new System.Drawing.Point(160, 12);
            this.LeafPanel.Name = "LeafPanel";
            this.LeafPanel.Size = new System.Drawing.Size(688, 426);
            this.LeafPanel.TabIndex = 2;
            this.LeafPanel.Visible = false;
            // 
            // LeafPanelListView
            // 
            this.LeafPanelListView.Alignment = System.Windows.Forms.ListViewAlignment.Left;
            this.LeafPanelListView.BackColor = System.Drawing.SystemColors.Window;
            this.LeafPanelListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader3,
            this.columnHeader4,
            this.columnHeader5,
            this.columnHeader6});
            this.LeafPanelListView.ForeColor = System.Drawing.SystemColors.WindowText;
            this.LeafPanelListView.FullRowSelect = true;
            this.LeafPanelListView.HideSelection = false;
            this.LeafPanelListView.Location = new System.Drawing.Point(0, 45);
            this.LeafPanelListView.Name = "LeafPanelListView";
            this.LeafPanelListView.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.LeafPanelListView.Size = new System.Drawing.Size(682, 71);
            this.LeafPanelListView.TabIndex = 1;
            this.LeafPanelListView.UseCompatibleStateImageBehavior = false;
            this.LeafPanelListView.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "Imie";
            this.columnHeader3.Width = 165;
            // 
            // columnHeader4
            // 
            this.columnHeader4.Text = "Nazwisko";
            this.columnHeader4.Width = 185;
            // 
            // columnHeader5
            // 
            this.columnHeader5.Text = "Data Urodzenia";
            this.columnHeader5.Width = 164;
            // 
            // columnHeader6
            // 
            this.columnHeader6.Text = "Miasto";
            this.columnHeader6.Width = 152;
            // 
            // LeafPanelButton
            // 
            this.LeafPanelButton.Location = new System.Drawing.Point(3, 3);
            this.LeafPanelButton.Name = "LeafPanelButton";
            this.LeafPanelButton.Size = new System.Drawing.Size(126, 36);
            this.LeafPanelButton.TabIndex = 0;
            this.LeafPanelButton.Text = "Edytuj Użytkownika";
            this.LeafPanelButton.UseVisualStyleBackColor = true;
            this.LeafPanelButton.Click += new System.EventHandler(this.LeafPanelButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(860, 450);
            this.Controls.Add(this.LeafPanel);
            this.Controls.Add(this.NodePanel);
            this.Controls.Add(this.treeView1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.NodePanel.ResumeLayout(false);
            this.LeafPanel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TreeView treeView1;
        private System.Windows.Forms.Panel NodePanel;
        private System.Windows.Forms.Button NodePanelButton;
        private System.Windows.Forms.ListView NodePanelListView;
        private System.Windows.Forms.Panel LeafPanel;
        private System.Windows.Forms.Button LeafPanelButton;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ListView LeafPanelListView;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.ColumnHeader columnHeader4;
        private System.Windows.Forms.ColumnHeader columnHeader5;
        private System.Windows.Forms.ColumnHeader columnHeader6;
    }
}

