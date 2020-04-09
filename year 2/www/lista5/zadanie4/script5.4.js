var canvas = document.getElementById("trojkat");
var ctx = canvas.getContext("2d");

var iter = 0;

var Ax = 0;
var Ay = 300;
    
var Bx = 300;
var By = 300;
    
var Cx = 150;
var Cy = 0;
    
var choosenX = 0;
var choosenY = 150;

var limit = 50;

function drawSierp() 
{
    for(i = 0; i < 5; i++) {
        
        var rand = Math.random()*3;

        
        if(rand < 1)
            {
                var middleX = (Ax + choosenX)/2;
                var middleY = (Ay + choosenY)/2;
            }
        else if(rand < 2)
            {
                var middleX = (Bx + choosenX)/2;
                var middleY = (By + choosenY)/2;
            }
        else 
            {
                var middleX = (Cx + choosenX)/2;
                var middleY = (Cy + choosenY)/2;
            }
        
        ctx.fillRect(middleX,middleY,1,1);
        choosenX = middleX;
        choosenY = middleY;
        
        $('#debug').html("Liczba iteracji: " + (iter+1));
        iter+=1; 
    }
    if(iter<limit)
            setTimeout(drawSierp, 1);   
}

function init()
{
    limit = prompt("Wpisz limit górny iteracji algorytmu (zalecane koło 10000): ", 10000);
    drawSierp();
}

$(init());