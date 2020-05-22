using l7z2.Properties;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace l7z2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private ClickActions clickActions;
        private Organiztor organizator;
        private Button buttonClicked = null;
        private bool insertAction = true;
        private Point picturePoint;
        private Point mousePoint;

        private void Form1_Load(object sender, EventArgs e)
        {
            this.clickActions = new ClickActions(this);
            this.organizator = new Organiztor(this);
            this.clickActions.Actions.Add(CircleButton, this.clickActions.AddCircle);
            this.organizator.Register(CircleButton, typeof(CreateMemento));
            this.clickActions.Actions.Add(SquareButton, this.clickActions.AddSquare);
            this.organizator.Register(SquareButton, typeof(CreateMemento));
            this.clickActions.Actions.Add(RectangleButton, this.clickActions.AddRectangle);
            this.organizator.Register(RectangleButton, typeof(CreateMemento));
            this.clickActions.Actions.Add(DeleteButton, this.clickActions.Delete);
            this.organizator.Register(DeleteButton, typeof(DeleteMemento));
            this.organizator.Register(MoveButton, typeof(MoveMemento));
        }

        private void Form1_Click(object sender, EventArgs e)
        {
            if (this.buttonClicked == null)
                return;
            if (this.insertAction == false)
                return;
            PictureBox addedPicture = this.clickActions.Actions[this.buttonClicked](null);
            addedPicture.MouseClick += new MouseEventHandler(Picture_Click);
            addedPicture.MouseMove += new MouseEventHandler(Picture_MouseMove);
            addedPicture.MouseDown += new MouseEventHandler(Picture_MouseDown);
            addedPicture.MouseUp += new MouseEventHandler(Picture_MouseUp);
            Memento state = this.organizator.MakeMemento(this.buttonClicked);
            state.Picture = addedPicture;
            this.organizator.SetState(state);
        }

        private void Picture_Click(object sender, MouseEventArgs e)
        {
            if (this.buttonClicked != DeleteButton)
                return;
            PictureBox picture = sender as PictureBox;
            this.clickActions.Actions[this.buttonClicked](picture);
            Memento state = this.organizator.MakeMemento(this.buttonClicked);
            state.Picture = picture;
            this.organizator.SetState(state);
        }

        private void Picture_MouseDown(object sender, MouseEventArgs e)
        {
            if (this.buttonClicked != MoveButton)
                return;
            PictureBox picture = sender as PictureBox;
            this.picturePoint = new Point(picture.Left, picture.Top);
            this.mousePoint = e.Location;
        }

        private void Picture_MouseMove(object sender, MouseEventArgs e)
        {
            if (this.buttonClicked != MoveButton)
                return;
            if (e.Button == MouseButtons.Left)
            {
                PictureBox picture = sender as PictureBox;
                picture.Left += e.X - this.mousePoint.X;
                picture.Top += e.Y - this.mousePoint.Y;
            }
        }

        private void Picture_MouseUp(object sender, MouseEventArgs e)
        {
            if (this.buttonClicked != MoveButton)
                return;
            PictureBox picture = sender as PictureBox;
            Memento state = this.organizator.MakeMemento(this.buttonClicked);
            state.Picture = picture;
            state.LastPosition = this.picturePoint;
            this.organizator.SetState(state);
        }

        private void CircleButton_Click(object sender, EventArgs e)
        {
            this.buttonClicked = CircleButton;
            this.insertAction = true;
        }

        private void SquareButton_Click(object sender, EventArgs e)
        {
            this.buttonClicked = SquareButton;
            this.insertAction = true;
        }

        private void RectangleButton_Click(object sender, EventArgs e)
        {
            this.buttonClicked = RectangleButton;
            this.insertAction = true;
        }

        private void MoveButton_Click(object sender, EventArgs e)
        {
            this.buttonClicked = MoveButton;
            this.insertAction = false;
        }

        private void DeleteButton_Click(object sender, EventArgs e)
        {
            this.buttonClicked = DeleteButton;
            this.insertAction = false;
        }

        private void UndoButton_Click(object sender, EventArgs e)
        {
            this.organizator.Undo();
            this.insertAction = false;
        }

        private void RedoButton_Click(object sender, EventArgs e)
        {
            this.organizator.Redo();
            this.insertAction = false;
        }
    }

    public class ClickActions
    {
        private Form _form;

        public delegate PictureBox ClickAction(PictureBox picture);
        public Dictionary<Button, ClickAction> Actions;

        public ClickActions(Form form)
        {
            this._form = form;
            this.Actions = new Dictionary<Button, ClickAction>();
        }

        private PictureBox startDrawing()
        {
            PictureBox picture = new PictureBox();
            Point point = new Point(Cursor.Position.X, Cursor.Position.Y);
            picture.Location = this._form.PointToClient(point);
            return picture;
        }

        public PictureBox AddCircle(PictureBox picture)
        {
            PictureBox NewPicture = startDrawing();
            NewPicture.Image = Resources.kolo;
            NewPicture.Size = new Size(100, 100);
            this._form.Controls.Add(NewPicture);
            return NewPicture;
        }

        public PictureBox AddSquare(PictureBox picture)
        {
            PictureBox NewPicture = startDrawing();
            NewPicture.Image = Resources.kwadrat;
            NewPicture.Size = new Size(100, 100);
            this._form.Controls.Add(NewPicture);
            return NewPicture;
        }

        public PictureBox AddRectangle(PictureBox picture)
        {
            PictureBox NewPicture = startDrawing();
            NewPicture.Image = Resources.prostokat;
            NewPicture.Size = new Size(200, 100);
            this._form.Controls.Add(NewPicture);
            return NewPicture;
        }

        public PictureBox Delete(PictureBox picture)
        {
            this._form.Controls.Remove(picture);
            return picture;
        }
    }

    public class Organiztor
    {
        Stack<Memento> undoStack = new Stack<Memento>();
        Stack<Memento> redoStack = new Stack<Memento>();
        private Dictionary<Button, Type> _subscribers =
            new Dictionary<Button, Type>();
        private Memento _state;
        private Form _form;

        public Organiztor(Form form)
        {
            this._form = form;
        }

        public void Register(Button button, Type type)
        {
            if (!type.IsSubclassOf(typeof(Memento)))
                throw new ArgumentException();

            _subscribers.Add(button, type);
        }

        public Memento MakeMemento(Button button)
        {
            Type mementoType = this._subscribers[button];
            Memento instance = (Memento)Activator.CreateInstance(mementoType);
            return instance;
        }

        public void Undo()
        {
            if (this.undoStack.Count > 0)
            {
                Memento m = undoStack.Pop();
                UndoMemento(m);
                redoStack.Push(m);
            }
        }
        public void Redo()
        {
            if (this.redoStack.Count > 0)
            {
                Memento m = redoStack.Pop();
                undoStack.Push(m);
                RedoMemento(m);
            }
        }
        private void StateChanged()
        {
            redoStack.Clear();
            undoStack.Push(this._state);
        }

        public void SetState(Memento memento)
        {
            this._state = memento;
            StateChanged();
        }
        

        private void UndoMemento(Memento m)
        {
            m.Undo(this._form);
        }

        private void RedoMemento(Memento m)
        {
            m.Redo(this._form);
        }
    }

    public abstract class Memento
    {
        public PictureBox Picture { get; set; }

        public Point LastPosition { get; set; }

        public abstract void Undo(Form form);

        public abstract void Redo(Form form);
    }

    public class CreateMemento : Memento
    {
        public override void Undo(Form form)
        {
            form.Controls.Remove(Picture);
        }

        public override void Redo(Form form)
        {
            form.Controls.Add(Picture);
        }
    }

    public class DeleteMemento : Memento
    {
        public override void Undo(Form form)
        {
            form.Controls.Add(Picture);
        }

        public override void Redo(Form form)
        {
            form.Controls.Remove(Picture);  
        }
    }

    public class MoveMemento : Memento
    {
        public override void Undo(Form form)
        {
            Point currPosition = new Point(Picture.Left, Picture.Top);
            Picture.Left = LastPosition.X;
            Picture.Top = LastPosition.Y;
            LastPosition = currPosition;
        }

        public override void Redo(Form form)
        {
            Point currPosition = new Point(Picture.Left, Picture.Top);
            Picture.Left = LastPosition.X;
            Picture.Top = LastPosition.Y;
            LastPosition = currPosition;
        }
    }

}

