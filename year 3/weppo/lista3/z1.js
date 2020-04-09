var obj = {
    pole: 5,
    metoda(){
        return this.pole
    },
    get numer(){
        return this.pole
    },
    set numer(x){
        this.pole = x
    }
}

console.log(obj.numer)
obj.numer = 66
console.log(obj.numer)

obj.pole2 = 'napis'
obj.metoda2 = function(){ return 'napis'}

console.log(obj.metoda2())

Object.defineProperty(obj, 'getter2', { get: function() { return this.pole2; } });
Object.defineProperty(obj, 'setter2', { set: function(x) { this.pole2 = x; } });
console.log(obj.getter2)
obj.setter2 = "inny napis"
console.log(obj.getter2)