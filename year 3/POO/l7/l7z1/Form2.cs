using System;
using System.Windows.Forms;

namespace l7z1
{
    public partial class Form2 : Form
    {
        private TreeView treeView;
        private string Node;
        private int Leaf;

        public Form2()
        {
            InitializeComponent();
        }

        public Form2(TreeView treeView, string Node, int Leaf, string Name,
            string Surname, string BirthDate, string City)
        {
            InitializeComponent();
            this.treeView = treeView;
            this.Node = Node;
            this.Leaf = Leaf;
            NameTextBox.Text = Name;
            SurnameTextBox.Text = Surname;
            BirthDateTimePicker.Value = Convert.ToDateTime(BirthDate);
            CityTextBox.Text = City;
        }

        private void SaveButton_Click(object sender, EventArgs e)
        {
            EventAggregator eventAggregator = EventAggregator.Instance();
            eventAggregator.Publish<UserEdited>(new UserEdited
            {
                Node = this.Node,
                LeafIndex = this.Leaf,
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
