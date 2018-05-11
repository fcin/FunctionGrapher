var width = 600;
var height = 600;



function setup()
{
    createCanvas(width, height);

    var input = "(6894 + 1247) * (643 + 1248)";
    var evaluator = new Evaluator(new Parser());
    var evaluatedResult = evaluator.evaluate(input);

    console.log("INPUT: " + input);
    console.log("RESULT: " + evaluatedResult);
}

function draw()
{
    background(255);
}
