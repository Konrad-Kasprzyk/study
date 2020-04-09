var Tree = function(left,right, val){
    this.left = left;
    this.right = right;
    this.val = val;
}

var Root = new Tree(null,null,10);
var Node1 = new Tree(null,null,9);
var Node2 = new Tree(null,null,8);
var Node3 = new Tree(null,null,7);

Root.left = Node1;
Node1.left = Node2;
Node2.left = Node3;

console.log(Root.left.left.left.val);
console.log(Root.right);


// Dlaczego to nie działa?
function* ValIter(node = this) {
    console.log("poczatek iteratora");

    if (node.left){
        console.log("lewy wezel");
        //ValIter(node.left);
        //yield this.left; - nie tak
        //for ( var e of this.left ) yield e; // ok
        yield* this.left;
        console.log("lewy wezel - koniec");
    }
    yield node.val;
    if (node.right){
        console.log("prawy wezel");
        yield* this.right;
        //ValIter(node.right);
    }
       
  }



Tree.prototype[Symbol.iterator] = ValIter;

for (var e of Root){
    console.log(e);
}

