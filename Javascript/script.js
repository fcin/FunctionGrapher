var canvasWidth = 600;
var canvasHeight = 600;

var range = { minX: -10, maxX: 10,
              minY: -10, maxY: 10 }

var points = 100;
var canvasZoom = 1;
var input = '';

function setup()
{
    createCanvas(canvasWidth, canvasHeight);
    frameRate(10);

    input = document.getElementById('functionInput').value;
    document.getElementById('drawBtn').addEventListener("click", function( event ) {
        input = document.getElementById('functionInput').value;
      }, false);
}

function draw()
{
    background(255);
    drawAxis();

    if(input.trim() === '')
        return;

    var evaluator = new Evaluator(new Parser());
    var interval = (Math.abs(range.minX) + Math.abs(range.maxX)) / points;

    noFill();
    beginShape();
    for(var index = range.minX; index < range.maxX; index += interval)
    {
        var evaluatedResult = evaluator.evaluate(input, index);
        if(evaluatedResult.hasError)
        {
            document.getElementById('errorLabel').innerHTML = evaluatedResult.error;
            return;
        }
        else
        {
            document.getElementById('errorLabel').innerHTML = '';
        }

        var scaleX = ((index - range.minX) / (range.maxX - range.minX)) * (canvasWidth - 0) + 0;
        var scaleY = canvasHeight - (((evaluatedResult.value - range.minY) / (range.maxY - range.minY)) * (canvasHeight - 0) + 0);

        curveVertex(scaleX, scaleY);
    }
    endShape();
}

function mouseWheel(event) {
    if(Math.abs(range.maxX) + Math.abs(range.minX) < 4 && event.delta < 0)
        return;

    canvasZoom += event.delta / 1000;

    range = { 
            minX: -10 * canvasZoom, maxX: 10 * canvasZoom, 
            minY: -10 * canvasZoom, maxY: 10 * canvasZoom 
        }
}

function drawAxis()
{
    line(canvasWidth / 2, 0, canvasWidth / 2, canvasHeight); // y
    line(0, canvasHeight / 2, canvasWidth, canvasHeight / 2); // x

    fill(70);

    var interval = 1;
    var fixedDecimals = 0;

    if(Math.abs(range.maxX) + Math.abs(range.minX) <= 6)
    {
        interval = 0.3;
        fixedDecimals = 1;
    }

    if(Math.abs(range.maxX) + Math.abs(range.minX) > 25)
        interval = 5;

    for(var index = range.maxY; index >= range.minY; index -= interval)
    {
        if(index === 0)
            continue;
        var scaleY = canvasHeight - (((index - range.minY) / (range.maxY - range.minY)) * (canvasHeight - 0) + 0);
        text((+index).toFixed(fixedDecimals), canvasWidth / 2, scaleY);
    }

    for(var index = range.minX; index < range.maxX; index += interval)
    {
        var scaleX = ((index - range.minX) / (range.maxX - range.minX)) * (canvasWidth - 0) + 0;
        text((+index).toFixed(fixedDecimals), scaleX, canvasHeight / 2);
    }
}