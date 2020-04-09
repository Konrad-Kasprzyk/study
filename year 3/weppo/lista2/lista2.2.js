let tab = [1,2,3]

const object = {
    x: 5,
    napis: 'szaman',
    y: 7
}

console.log(tab['2'])
console.log(tab['weppo'])
console.log(tab[object])
console.log(tab['object'])

/*
tab[7] = 4
console.log(tab[5])
console.log(tab[7])
console.log(tab)
*/

// tablica to obiekt, więc dopisuje się nowy klucz i jego wartość.
// długość tablicy nie zwiększa się
tab['weppo'] = 13
console.log(tab)
console.log(tab.length)

tab.length = 2
console.log(tab)

tab.length = 6
console.log(tab)