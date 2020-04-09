// Co to konkretnie są prototypty? Czy działają różnie ze względu że to jest obiekt lub funkcja. Co to prototyp funkcji wewnętrznego Foo
// Jak działają domknięcia? Czy po wywołaniu new Foo, ta funkcja zapomina o Bar i Qux i innych swoich zmiennych. Przeczy temu wykład 6 slajd 2.2, jak działa this w funkcjach
var Foo = (function(){

    function Bar(){
        Qux();
        console.log("Bar called Qux");
    }

    function Qux(){
        console.log("Qux called");
    }    

    function Foo(){}

    Foo.prototype.Bar = Bar;
    
    return Foo;
}());

console.log(Object.getPrototypeOf(Foo))

var p = new Foo();

console.log(Object.getPrototypeOf(p))

console.log(Object.getPrototypeOf(Object.getPrototypeOf(p)))

p.Bar();

