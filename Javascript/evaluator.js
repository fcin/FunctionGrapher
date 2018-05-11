function Evaluator(parser)
{
    this.parser = parser;

    /**
     * Calculates value for specified input.
     * @param {string} input 
     */
    this.evaluate = function(input)
    {
        input = this.parser.parse(input).split(',');
        
        var index = 0;
        while(index < input.length)
        {
            var token = input[index];

            if(this.parser.isOperator(token))
            {
                var lastOperand = input[index - 2];
                var lastOperand2 = input[index - 1];
                var result = '';

                switch(token)
                {
                    case '+' : result = (+lastOperand) + (+lastOperand2); break;
                    case '-' : result = (+lastOperand) - (+lastOperand2); break;
                    case '*' : result = (+lastOperand) * (+lastOperand2); break;
                    case '/' : result = (+lastOperand) / (+lastOperand2); break;
                }

                input.splice(index + 1, 0, result);
                input.splice(index - 0, 1); // op1
                input.splice(index - 1, 1); // op2
                input.splice(index - 2, 1); // operator
                index = 0;
            }

            index++;
        }

        // Return accumulated value.
        return input[0];
    }
}