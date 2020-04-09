var srodekBool = false; /* czy środkowy kwadrat został najechany po rozpoczęciu gry */
var najechanyKwadratBool = false; /* czy jakiś zewnętrzny kwadrat został najechany zanim 
                                    dotarliśmy do środkowego kwadratu */
var kwadratBool = new Array (6); /* domyślnie w tablicy jest ustawione false,
                                   czyli początkowo kwadraty nie są najechane  */
var graAktywnaBool = true;
var tab = document.getElementsByClassName("kwadrat");
var czas = 0.00;
var liczCzasInterval;
var wyniki = document.getElementsByClassName("wyniki");
var wynikiArray = new Array (5);

window.onload = function() {
   losujKwadraty();
   document.getElementById("srodek").onmouseover = function() {najedzSrodek()};
   document.getElementById("srodek").onmouseleave = function() {zjedzSrodek()};
   document.getElementById("restart").onmousedown = function() {nowaGra()};
   
        tab[0].onmouseover = function() {najedzKwadrat(0)};
        tab[1].onmouseover = function() {najedzKwadrat(1)};
        tab[2].onmouseover = function() {najedzKwadrat(2)};
        tab[3].onmouseover = function() {najedzKwadrat(3)};
        tab[4].onmouseover = function() {najedzKwadrat(4)};
        tab[5].onmouseover = function() {najedzKwadrat(5)};
        
      /* for(var j=0; j<5; j++)                                             DLACZEGO TO NIE DZIAŁA??
        tab[j].onmouseover = function() {najedzKwadrat(j)};                 oraz dlaczego musi być function() {najedzKwadrat(5)}; zamiast najedzKwadrat(5)
        */

    for(var i=0; i<5; i++)
        wynikiArray[i] = 0.00;
  };

function losuj(przesun)
{
    return Math.floor((Math.random() * 15) + przesun)
}

function losujKwadraty()
{
    tab[0].style.top = losuj(20) + "%";
    tab[0].style.left = losuj(15) + "%";
    tab[1].style.top = losuj(20) + "%";
    tab[1].style.left = losuj(65) + "%";
    tab[2].style.top = losuj(60) + "%";
    tab[2].style.left = losuj(15) + "%";
    tab[3].style.top = losuj(60) + "%";
    tab[3].style.left = losuj(65) + "%";
    tab[4].style.top = losuj(5) + "%";
    tab[4].style.left = losuj(40) + "%";
    tab[5].style.top = losuj(70) + "%";
    tab[5].style.left = losuj(40) + "%";
}

function zjedzSrodek(){
    if (graAktywnaBool == true){
        czasStart();
    }
}

function najedzSrodek(){
    if (graAktywnaBool == true)
    {
        /* najechanie kwadratu przy załadowaniu strony lub nowej grze */
        srodekBool = true;
        /* po najechaniu na zewnętrzny kwdrat dzięki temu możemy najechać na inny zewnętrzny */
        najechanyKwadratBool = false;
        czasStop();
        /* sprawdzam czy najechane zostały wszystkie kwadraty */
        var licznik = 0;
        for(var i=0; i<6; i++){
            if (kwadratBool[i] ==true)
                licznik++;
        }
        if (licznik == 6){
            graAktywnaBool = false;
            
            for(var i=0; i<6; i++)
                kwadratBool[i] = false;                

            /* mamy zapełnioną tablicę wyników, sprawdzamy czy nasz czas jest na tyle dobry by umieścić go w tabeli */
            if (wynikiArray[4] > czas){
                wynikiArray[4] = czas;
                wynikiArray.sort()
                for (var i=0; i<5; i++)
                    wyniki[i].innerHTML = wynikiArray[i].toFixed(2).toString();
            }
            /* nie mamy zapełnionej tabeli wyników */
            else{
                /* mamy zapełnioną całą tablicę, więc nie nadpisujemy ostatniego najlepszego wyniku gorszym */
                if (wynikiArray[4] != 0.00) return;
                wynikiArray[4] = czas;
                /* te sortowanie wypycha zera na dół, a zwykłe liczby porównuje nomralnie */
                wynikiArray.sort(function(a, b){
                    if(a == 0.00 || b == 0.00)  return b-a;
                    return a-b;})
                for (var i=0; i<5; i++)
                    wyniki[i].innerHTML = wynikiArray[i].toFixed(2).toString();
            }      
        }
    }
            
}

function najedzKwadrat(i){
    if (graAktywnaBool == true && srodekBool == true){
        if (najechanyKwadratBool == true)
            return;
        if (kwadratBool[i] == true)
            czas += 1.5;
        najechanyKwadratBool = true;
        kwadratBool[i] = true;
        tab[i].style.backgroundColor = "#ff99ff";
    }
}

function dodawajCzas(){
    czas += 0.01;
    document.getElementById("czas").innerHTML = czas.toFixed(2);
}

function czasStart(){
    liczCzasInterval = setInterval(dodawajCzas, 10);
}

function czasStop(){
    clearInterval(liczCzasInterval);
}

function nowaGra(){
    czasStop();
    czas = 0.00;
    document.getElementById("czas").innerHTML = czas.toFixed(2);
    graAktywnaBool = true;
    srodekBool = false;
    for(var i=0; i<6; i++){
        kwadratBool[i] = false;          
    }
    for(var i=0; i<6; i++){
        tab[i].style.backgroundColor = "#009933"; 
    }
    losujKwadraty();
}