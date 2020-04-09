// w obydwu [] i . mogę odnieść się do składowej w obiekcie
// w [] mogę umieścić zmienną lub obiekt
// w . mogę wywołać tylko pola w obiekcie

const object = {
    x: 5,
    napis: 'szaman',
    y: 7
}

const object2 = {
    a: 1,
    b: 2,
    napis: 'szaman',
    toString: function() {
        return 'jakiś klucz'
    }
}

// undefined
//console.log(object[1])
//console.log(object[object2])

// nawiasy i bez nawiasów nie dają innego wyniku
object['1'] = 12
object[1] = 10

console.log(object['1'])
console.log(object[1])

object[object2] = 30
object['object2'] = 32

console.log(object[object2])
console.log(object['object2'])

console.log( object2.toString() );

var keys = Object.keys(object);
for ( var i=0; i<keys.length; i++ )
{
    console.log( `klucz: ${keys[i]}` );
}

