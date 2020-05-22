using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace l7z1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            NodePanel.Visible = true;
            DataHolder dataHolder = new DataHolder();
            ViewsManager viewsManager = new ViewsManager(dataHolder);
            EventAggregator eventAggregator = EventAggregator.Instance();
            eventAggregator.AddSubscriber<NodeClicked>(viewsManager);
            eventAggregator.AddSubscriber<LeafClicked>(viewsManager);
            eventAggregator.AddSubscriber<AddButtonClicked>(viewsManager);
            eventAggregator.AddSubscriber<EditButtonClicked>(viewsManager);
            eventAggregator.AddSubscriber<RebuildTree>(viewsManager);
            eventAggregator.AddSubscriber<UserAdded>(dataHolder);
            eventAggregator.AddSubscriber<UserEdited>(dataHolder);
            eventAggregator.Publish<RebuildTree>(new RebuildTree { treeView = treeView1});
        }

        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            EventAggregator eventAggregator = EventAggregator.Instance();
            if (e.Node.Tag == null)
            {
                eventAggregator.Publish<NodeClicked>(new NodeClicked 
                {
                    NodeName = e.Node.Text,
                    LeafPanel = LeafPanel,
                    NodePanel = NodePanel
                });
            }
            else
            {
                eventAggregator.Publish<LeafClicked>(new LeafClicked
                {
                    NodeName = e.Node.Name,
                    LeafHash = (int)e.Node.Tag,
                    LeafPanel = LeafPanel,
                    NodePanel = NodePanel
                });
            }
        }

        private void NodePanelButton_Click(object sender, EventArgs e)
        {
            EventAggregator eventAggregator = EventAggregator.Instance();
            eventAggregator.Publish<AddButtonClicked>(new AddButtonClicked 
            { 
                treeView = treeView1,
                form1 = this
            });
        }

        private void LeafPanelButton_Click(object sender, EventArgs e)
        {
            EventAggregator eventAggregator = EventAggregator.Instance();
            eventAggregator.Publish<EditButtonClicked>(new EditButtonClicked
            {
                treeView = treeView1,
                User = LeafPanelListView.Items[0],
                View = LeafPanelListView
            });
        }
    }

    // język komunikacji

    public class UserAdded
    {
        TreeView treeView { get; set; }
        public string Node { get; set; }
        public string Name { get; set; }
        public string Surname { get; set; }
        public DateTime BirthDate { get; set; }
        public string City { get; set; }
    }

    public class UserEdited
    {
        TreeView treeView { get; set; }
        public string Node { get; set; }
        public int LeafIndex { get; set; }
        public string Name { get; set; }
        public string Surname { get; set; }
        public DateTime BirthDate { get; set; }
        public string City { get; set; }
    }

    public class NodeClicked 
    {
        public string NodeName { get; set; }
        public Panel LeafPanel { get; set; }
        public Panel NodePanel { get; set; }
    }

    public class LeafClicked
    {
        public string NodeName { get; set; }
        public int LeafHash { get; set; }
        public Panel LeafPanel { get; set; }
        public Panel NodePanel { get; set; }
    }

    public class RebuildTree
    {
        public TreeView treeView { get; set; }
    }

    public class AddButtonClicked
    {
        public Form form1 { get; set; }
        public TreeView treeView { get; set; }
    }
    public class EditButtonClicked
    {
        public ListView View { get; set; }
        public TreeView treeView { get; set; }
        public ListViewItem User { get; set; }
    }

    // Uczestnicy

    public class DataHolder :
        ISubscriber<UserAdded>,
        ISubscriber<UserEdited>
    {
        public Dictionary<string, List<ListViewItem>> Nodes;

        public DataHolder()
        {
            Nodes = new Dictionary<string, List<ListViewItem>>();
            List<ListViewItem> Studenci = new List<ListViewItem>();
            ListViewItem lvi = new ListViewItem("Antek");
            lvi.SubItems.Add("Musiał");
            lvi.SubItems.Add(new DateTime(1999, 4, 25).Date.ToString());
            lvi.SubItems.Add("Świdnica");
            Studenci.Add(lvi);
            lvi = new ListViewItem("Karol");
            lvi.SubItems.Add("Gacek");
            lvi.SubItems.Add(new DateTime(1998, 8, 15).Date.ToString());
            lvi.SubItems.Add("Wrocław");
            Studenci.Add(lvi);
            Nodes["Studenci"] = Studenci;
            List<ListViewItem> Prowadzacy = new List<ListViewItem>();
            lvi = new ListViewItem("Kuba");
            lvi.SubItems.Add("Chałupka");
            lvi.SubItems.Add(new DateTime(1978, 1, 11).Date.ToString());
            lvi.SubItems.Add("Dzierżoniów");
            Prowadzacy.Add(lvi);
            lvi = new ListViewItem("Małgorzata");
            lvi.SubItems.Add("Majewska");
            lvi.SubItems.Add(new DateTime(1976, 9, 28).Date.ToString());
            lvi.SubItems.Add("Uciechów");
            Prowadzacy.Add(lvi);
            Nodes["Prowadzący"] = Prowadzacy;
        }

        public void Handle(UserAdded Notification)
        {
            ListViewItem lvi = new ListViewItem(Notification.Name);
            lvi.SubItems.Add(Notification.Surname);
            lvi.SubItems.Add(Notification.BirthDate.Date.ToString());
            lvi.SubItems.Add(Notification.City);
            Nodes[Notification.Node].Add(lvi);
        }

        public void Handle(UserEdited Notification)
        {
            ListViewItem lvi = new ListViewItem(Notification.Name);
            lvi.SubItems.Add(Notification.Surname);
            lvi.SubItems.Add(Notification.BirthDate.Date.ToString());
            lvi.SubItems.Add(Notification.City);
            Nodes[Notification.Node][Notification.LeafIndex] = lvi;
        }
    }

    public class ViewsManager :
        ISubscriber<NodeClicked>,
        ISubscriber<LeafClicked>,
        ISubscriber<EditButtonClicked>,
        ISubscriber<AddButtonClicked>,
        ISubscriber<RebuildTree>
    {
        private DataHolder _dataHolder;
        private string _lastViewedNode;
        private int _lastViewedLeafIndex;
        public ViewsManager(DataHolder dataHolder)
        {
            this._dataHolder = dataHolder;
            this._lastViewedNode = dataHolder.Nodes.Keys.First();
            this._lastViewedLeafIndex = 0;
        }

        public void Handle(NodeClicked Notification)
        {
            string nodeName = Notification.NodeName;
            this._lastViewedNode = nodeName;
            ListView view = Notification.NodePanel.Controls.Find(
                "NodePanelListView", false).FirstOrDefault() as ListView;
            if (view.Items.Count > 0)
                view.Items.Clear();
            foreach (ListViewItem leaf in this._dataHolder.Nodes[nodeName])
            {
                leaf.Remove();
                view.Items.Add(leaf);
            }
            Notification.LeafPanel.Visible = false;
            Notification.NodePanel.Visible = true;   
        }

        public void Handle(LeafClicked Notification)
        {
            string nodeName = Notification.NodeName;
            this._lastViewedNode = nodeName;
            ListView view = Notification.LeafPanel.Controls.Find(
                "LeafPanelListView", false).FirstOrDefault() as ListView;
            if (view.Items.Count > 0)
                view.Items.Clear();
            ListViewItem leaf;
            // Searching for index of leaf in DataHolder
            for (int i=0; i< this._dataHolder.Nodes[nodeName].Count; i++)
            {
                if (this._dataHolder.Nodes[nodeName][i].GetHashCode() == Notification.LeafHash)
                {
                    leaf = this._dataHolder.Nodes[nodeName][i];
                    this._lastViewedLeafIndex = i;
                    leaf.Remove();
                    view.Items.Add(leaf);
                    break;
                }
            }
            Notification.NodePanel.Visible = false;
            Notification.LeafPanel.Visible = true;
        }

        public void Handle(EditButtonClicked Notification)
        {
            ListViewItem leaf = this._dataHolder.Nodes[this._lastViewedNode][this._lastViewedLeafIndex];
            
            Form2 f2 = new Form2(Notification.treeView, this._lastViewedNode, this._lastViewedLeafIndex,
                leaf.SubItems[0].Text, leaf.SubItems[1].Text, leaf.SubItems[2].Text, leaf.SubItems[3].Text);
            f2.ShowDialog();
            leaf = this._dataHolder.Nodes[this._lastViewedNode][this._lastViewedLeafIndex];
            Notification.View.Items[0] = leaf;
        }

        public void Handle(AddButtonClicked Notification)
        {
            Form3 f3 = new Form3(Notification.treeView, this._lastViewedNode);
            f3.ShowDialog();
            EventAggregator eventAggregator = EventAggregator.Instance();
            eventAggregator.Publish<NodeClicked>(new NodeClicked
            {
                NodeName = this._lastViewedNode,
                LeafPanel = Notification.form1.Controls.Find("LeafPanel", false).FirstOrDefault() as Panel,
                NodePanel = Notification.form1.Controls.Find("NodePanel", false).FirstOrDefault() as Panel
            });
        }

        public void Handle(RebuildTree Notification)
        {
            TreeView treeView = Notification.treeView;
            if (treeView.Nodes.Count > 0)
                treeView.Nodes.Clear();
            foreach (string node in this._dataHolder.Nodes.Keys)
            {
                treeView.Nodes.Add(node);
                foreach (ListViewItem leaf in this._dataHolder.Nodes[node])
                {
                    int node_number = treeView.Nodes.Count - 1;
                    treeView.Nodes[node_number].Nodes.Add(leaf.SubItems[0].Text);
                    int leaf_numer = treeView.Nodes[node_number].Nodes.Count - 1;
                    treeView.Nodes[node_number].Nodes[leaf_numer].Tag = leaf.GetHashCode();
                    treeView.Nodes[node_number].Nodes[leaf_numer].Name = node;
                }
            }
        }
    }

    // EventAggregator i interfejsy

    public interface ISubscriber<T>
    {
        void Handle(T Notification);
    }

    public interface IEventAggregator
    {
        void AddSubscriber<T>(ISubscriber<T> Subscriber);
        void RemoveSubscriber<T>(ISubscriber<T> Subscriber);
        void Publish<T>(T Event);
    }

    public class EventAggregator : IEventAggregator
    {
        Dictionary<Type, List<object>> _subscribers =
        new Dictionary<Type, List<object>>();

        private static EventAggregator _instance;
        private static object _lock = new object();

        public static EventAggregator Instance() 
        {
            if (_instance == null)
            {
                lock (_lock)
                {
                    if (_instance == null)
                    {
                        _instance = new EventAggregator();
                    }
                }
            }

            return _instance;
        }

        #region IEventAggregator Members
        public void AddSubscriber<T>(ISubscriber<T> Subscriber)
        {
            if (!_subscribers.ContainsKey(typeof(T)))
                _subscribers.Add(typeof(T), new List<object>());
            _subscribers[typeof(T)].Add(Subscriber);
        }
        public void RemoveSubscriber<T>(ISubscriber<T> Subscriber)
        {
            if (_subscribers.ContainsKey(typeof(T)))
                _subscribers[typeof(T)].Remove(Subscriber);
        }

        public void Publish<T>(T Event)
        {
            if (_subscribers.ContainsKey(typeof(T)))
                foreach (ISubscriber<T> subscriber in
                _subscribers[typeof(T)].OfType<ISubscriber<T>>())
                    subscriber.Handle(Event);
        }
        #endregion
    }

}
