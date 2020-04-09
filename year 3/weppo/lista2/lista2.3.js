console.log( (![]+[])[+[]]+
                (![]+[])[+!+[]]+
                    ([![]]+[][[]])[+!+[]+[+[]]]+
                        (![]+[])[!+[]+!+[]] );
// [] + [] => "" + "" => ""     czyli pusty napis
// [1,2] + [3,4] => "1,2" + "3,4" => "1,23,4"

// In JavaScript, it is true that +[] === 0. + converts something into a number,
// and in this case it will come down to +"" or 0       czyl +[] => 0

// 3 + 4 + +"5" == (3 + 4) + (+"5") == 7 + (+"5") == 7 + 5 == 12

// +3 == 3,   +'3' == 3

// (+[] + 1) === (+"" + 1)
// (+"" + 1) === (0 + 1)
// (0 + 1) === 1

// [] == false

// ![] === false
// !![] === true

// !'' === true
// !'a' === false

// operator + konwertuje pierw na string, a potem na number
// ![] === false   String(![]) == napis "false"  , napis "false" + "" == "false"
// (![]+[]) == "false"
// [+[]] == [ 0 ]
// (![]+[])[+[]] == "false"[ 0 ] == 'f'

// +!+[] -> + zamienia [] na liczbę, czyli zero.   ! zamienia na bool i neguje, czyli mamy true.
// + zamienia na liczbe i mamy 1         [ +!+[] ] == [1]
// (![]+[])[+!+[]] == "false"[ 1 ] == 'a'


// ![] === false    (![] + []) = "false"
// [][[]] === 'undefined        ([![]]+[][[]]) == "falseundefined"
// [+!+[] + [+[]]]) = "1" + "0" = "10"
// + konwertuje tablice na string
// "falseundefined"[ 10 ] == 'i'

// (![] + []) = "false" + "" = "false"
// [!+[] + !+[]] = [1 + 1] = [2]
// "false"[ 2 ] == 'l'

