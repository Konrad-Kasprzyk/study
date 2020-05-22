using System;
using System.Windows.Forms;

namespace l7z1
{
    public partial class Form3 : Form
    {
        private TreeView treeView;
        private string Node;

        public Form3()
        {
            InitializeComponent();
        }

        public Form3(TreeView treeView, string Node)
        {
            InitializeComponent();
            this.treeView = treeView;
            this.Node = Node;
        }

        private void SaveButton_Click(object sender, EventArgs e)
        {
            EventAggregator eventAggregator = EventAggregator.Instance();
            eventAggregator.Publish<UserAdded>(new UserAdded
            {
                Node = this.Node,
                Name = NameTextBox.Text,
                Surname = SurnameTextBox.Text,
                BirthDate = BirthDateTimePicker.Value,
                City = CityTextBox.Text
            });
            eventAggregator.Publish<RebuildTree>(new RebuildTree { treeView = this.treeView });
            Close();
        }
    }
}
