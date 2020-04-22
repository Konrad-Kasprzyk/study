using System;

namespace Lista6
{
    class l6z3
    {
        public static void Main_z3()
        {
            Console.WriteLine("Lista 6, zadanie 3");

            Tree root = new TreeNode()
            {
                Left = new TreeNode()
                {
                    Left = new TreeNode()
                    {
                        Left = new TreeLeaf() { Value = 5},
                        Right = new TreeLeaf() { Value = 6 }
                    },
                    Right = new TreeLeaf() { Value = 1 }
                },
                Right = new TreeLeaf() { Value = 3 }
            };
            DepthTreeVisitor visitor = new DepthTreeVisitor();
            visitor.Visit(root);
            Console.WriteLine("Głębokość drzewa to {0}", visitor.Depth);
            Console.ReadLine();
        }
    }

    public abstract class Tree
    {
    }
    public class TreeNode : Tree
    {
        public Tree Left { get; set; }
        public Tree Right { get; set; }
    }
    public class TreeLeaf : Tree
    {
        public int Value { get; set; }
    }
    public class DepthTreeVisitor
    {
        public int Depth = 0;

        public int Visit(Tree tree)
        {
            if (tree is TreeNode)
                return this.VisitNode((TreeNode)tree);
            if (tree is TreeLeaf)
                return this.VisitLeaf((TreeLeaf)tree);
            throw new ArgumentException();
        }
        public int VisitNode(TreeNode node)
        {
            if (node != null)
            {
                int left = this.Visit(node.Left);
                int right = this.Visit(node.Right);
                if (left > right)
                {
                    if (left > Depth)
                        Depth = left;
                    return left + 1;
                }
                else
                {
                    if (right > Depth)
                        Depth = right;
                    return right + 1;
                }

            }
            else
            {
                return 0;
            }
        }

        
        public int VisitLeaf(TreeLeaf leaf)
        {
            return 1;
        }

    }
}
