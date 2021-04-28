
namespace Zadanie_2_1_2
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
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.TreeNode treeNode9 = new System.Windows.Forms.TreeNode("Child");
            System.Windows.Forms.TreeNode treeNode10 = new System.Windows.Forms.TreeNode("NestRoot", new System.Windows.Forms.TreeNode[] {
            treeNode9});
            System.Windows.Forms.TreeNode treeNode11 = new System.Windows.Forms.TreeNode("Child");
            System.Windows.Forms.TreeNode treeNode12 = new System.Windows.Forms.TreeNode("Root", new System.Windows.Forms.TreeNode[] {
            treeNode10,
            treeNode11});
            System.Windows.Forms.TreeNode treeNode13 = new System.Windows.Forms.TreeNode("13");
            System.Windows.Forms.TreeNode treeNode14 = new System.Windows.Forms.TreeNode("42");
            System.Windows.Forms.TreeNode treeNode15 = new System.Windows.Forms.TreeNode("49");
            System.Windows.Forms.TreeNode treeNode16 = new System.Windows.Forms.TreeNode("Numbers", new System.Windows.Forms.TreeNode[] {
            treeNode13,
            treeNode14,
            treeNode15});
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.buttonStartProgressBar = new System.Windows.Forms.Button();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.buttonResetProgressBar = new System.Windows.Forms.Button();
            this.listView1 = new System.Windows.Forms.ListView();
            this.SuspendLayout();
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // treeView1
            // 
            this.treeView1.Location = new System.Drawing.Point(11, 95);
            this.treeView1.Name = "treeView1";
            treeNode9.Name = "Node2";
            treeNode9.Text = "Child";
            treeNode10.Name = "Node1";
            treeNode10.Text = "NestRoot";
            treeNode11.Name = "Node3";
            treeNode11.Text = "Child";
            treeNode12.Name = "Node0";
            treeNode12.Text = "Root";
            treeNode13.Name = "Node5";
            treeNode13.Text = "13";
            treeNode14.Name = "Node6";
            treeNode14.Text = "42";
            treeNode15.Name = "Node8";
            treeNode15.Text = "49";
            treeNode16.Name = "Node4";
            treeNode16.Text = "Numbers";
            this.treeView1.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode12,
            treeNode16});
            this.treeView1.Size = new System.Drawing.Size(186, 182);
            this.treeView1.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 76);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(52, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "TreeView";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 291);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(0, 13);
            this.label2.TabIndex = 4;
            // 
            // buttonStartProgressBar
            // 
            this.buttonStartProgressBar.Location = new System.Drawing.Point(12, 12);
            this.buttonStartProgressBar.Name = "buttonStartProgressBar";
            this.buttonStartProgressBar.Size = new System.Drawing.Size(185, 23);
            this.buttonStartProgressBar.TabIndex = 1;
            this.buttonStartProgressBar.Text = "Start ProgressBar";
            this.buttonStartProgressBar.UseVisualStyleBackColor = true;
            this.buttonStartProgressBar.Click += new System.EventHandler(this.buttonStartProgressBar_Click);
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(12, 41);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(440, 23);
            this.progressBar1.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.progressBar1.TabIndex = 0;
            // 
            // buttonResetProgressBar
            // 
            this.buttonResetProgressBar.Location = new System.Drawing.Point(267, 12);
            this.buttonResetProgressBar.Name = "buttonResetProgressBar";
            this.buttonResetProgressBar.Size = new System.Drawing.Size(185, 23);
            this.buttonResetProgressBar.TabIndex = 6;
            this.buttonResetProgressBar.Text = "Reset ProgressBar";
            this.buttonResetProgressBar.UseVisualStyleBackColor = true;
            this.buttonResetProgressBar.Click += new System.EventHandler(this.buttonResetProgressBar_Click);
            // 
            // listView1
            // 
            this.listView1.HideSelection = false;
            this.listView1.Location = new System.Drawing.Point(228, 95);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(224, 182);
            this.listView1.TabIndex = 7;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(464, 395);
            this.Controls.Add(this.listView1);
            this.Controls.Add(this.buttonResetProgressBar);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.treeView1);
            this.Controls.Add(this.buttonStartProgressBar);
            this.Controls.Add(this.progressBar1);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TreeView treeView1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button buttonStartProgressBar;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.Button buttonResetProgressBar;
        private System.Windows.Forms.ListView listView1;
    }
}

