using System;
using System.Collections;
using System.Collections.Generic;

namespace Zadanie_1._2._2
{
    public class BinaryTreeNode<T>
    {
        private static Queue<BinaryTreeNode<T>> _queue = new Queue<BinaryTreeNode<T>>();
        private static Stack<BinaryTreeNode<T>> _stack = new Stack<BinaryTreeNode<T>>();
        
        public T Val { get; set; }
        public BinaryTreeNode<T>  Left { get; set; }
        public BinaryTreeNode<T>  Right { get; set; }

        public class DepthTraverseEnumerator : IEnumerable<T>, IEnumerator<T>
        {
            private BinaryTreeNode<T> _root;
            private BinaryTreeNode<T> _current;

            public DepthTraverseEnumerator(BinaryTreeNode<T> root)
            {
                this._root = root;
                BinaryTreeNode<T>._stack.Clear();
                BinaryTreeNode<T>._stack.Push(root);
            }
            public IEnumerator<T> GetEnumerator()
            {
                return this;
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                return GetEnumerator();
            }

            public void Dispose() {}

            public bool MoveNext()
            {
                if (BinaryTreeNode<T>._stack.Count == 0)
                    return false;
                _current = BinaryTreeNode<T>._stack.Pop();
                if (_current.Right != null)
                    BinaryTreeNode<T>._stack.Push(_current.Right);
                if (_current.Left != null)
                    BinaryTreeNode<T>._stack.Push(_current.Left);
                return true;
            }

            public void Reset()
            {
                BinaryTreeNode<T>._stack.Clear();
                BinaryTreeNode<T>._stack.Push(_root);
            }

            public T Current => _current.Val;

            object IEnumerator.Current => Current;
        }
        
        public class BreadthTraverseEnumerator : IEnumerable<T>, IEnumerator<T>
        {
            private BinaryTreeNode<T> _root;
            private BinaryTreeNode<T> _current;

            public BreadthTraverseEnumerator(BinaryTreeNode<T> root)
            {
                this._root = root;
                BinaryTreeNode<T>._queue.Clear();
                BinaryTreeNode<T>._queue.Enqueue(root);
            }
            
            public IEnumerator<T> GetEnumerator()
            {
                return this;
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                return GetEnumerator();
            }
            
            public void Dispose()
            {
                BinaryTreeNode<T>._queue.Clear();
            }

            public bool MoveNext()
            {
                if (_queue.Count == 0)
                    return false;
                _current = _queue.Dequeue();
                if (_current.Left != null)
                    _queue.Enqueue(_current.Left);
                if (_current.Right != null)
                    _queue.Enqueue(_current.Right);
                return true;
            }

            public void Reset()
            {
                BinaryTreeNode<T>._queue.Clear();
                BinaryTreeNode<T>._queue.Enqueue(_root);
            }

            public T Current => _current.Val;

            object IEnumerator.Current => Current;
        }

        public IEnumerable<T> BreadthTraverseNoYield()
        {
            return new BreadthTraverseEnumerator(this);
        }
        
        public IEnumerable<T> BreadthTraverseYield()
        {
            _queue.Clear();
            if (Left != null)
                _queue.Enqueue(Left);
            if (Right != null)
                _queue.Enqueue(Right);
            yield return Val;
            while (_queue.Count > 0)
            {
                BinaryTreeNode<T> nextNode = _queue.Dequeue();
                yield return nextNode.Val;
                if (nextNode.Left != null)
                    _queue.Enqueue(nextNode.Left);
                if (nextNode.Right != null)
                    _queue.Enqueue(nextNode.Right);
            }
        }
        
        public IEnumerable<T> DepthTraverseNoYield()
        {
            return new DepthTraverseEnumerator(this);
        }
        
        public IEnumerable<T> DepthTraverseYield()
        {
            yield return Val;
            
            if (Left != null)
            {
                foreach (T item in Left.DepthTraverseYield())
                    yield return item;
            }

            if (Right != null)
            {
                foreach (T item in Right.DepthTraverseYield())
                    yield return item;
            }
        }
    }
    
    internal class Program
    {
        public static void Main(string[] args)
        {
            //      Tree
            //                  1
            //            /          \
            //       2                   5
            //    /     \                    \
            //  3         4                      6
            //                                /
            //                              7
            BinaryTreeNode<int> root = new BinaryTreeNode<int>()
            {
                Left = new BinaryTreeNode<int>()
                {
                    Left = new BinaryTreeNode<int>()
                    {
                        Val = 3
                    },
                    Val = 2,
                    Right = new BinaryTreeNode<int>()
                    {
                        Val = 4
                    }
                },
                Val = 1,
                Right = new BinaryTreeNode<int>()
                {
                    Val = 5,
                    Right = new BinaryTreeNode<int>()
                    {
                        Left = new BinaryTreeNode<int>()
                        {
                            Val = 7
                        },
                        Val = 6
                    }
                }
            };
            Console.WriteLine("Breadth search with yield");
            foreach (int val in root.BreadthTraverseYield())
            {
                Console.WriteLine(val);
            }
            Console.WriteLine("Breadth search without yield");
            foreach (int val in root.BreadthTraverseNoYield())
            {
                Console.WriteLine(val);
            }
            Console.WriteLine("Depth search with yield");
            foreach (int val in root.DepthTraverseYield())
            {
                Console.WriteLine(val);
            }
            Console.WriteLine("Depth search without yield");
            foreach (int val in root.DepthTraverseNoYield())
            {
                Console.WriteLine(val);
            }
            
            Console.ReadKey();
        }
    }
}