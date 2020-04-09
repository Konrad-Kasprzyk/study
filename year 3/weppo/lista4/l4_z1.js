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

console.log(Object.getPrototypeOf(Root));
console.log(Object.getPrototypeOf(Node1));

console.log(Tree.prototype);


var person = {
    init : function(name){
        this.name = name;
    }
}

var p = Object.create(person);
p.init('ala');

// Co to właściwie są prototypy
console.log("----------------------------")
console.log(person.prototype);
console.log(Object.getPrototypeOf(p));

class Worker{
    constructor(name){
        this.name = name;
    }
}

var w = new Worker('ewa');

console.log("----------------------------")
console.log(Worker.prototype);
console.log(Worker.prototype.prototype);
console.log(Object.getPrototypeOf(w));
