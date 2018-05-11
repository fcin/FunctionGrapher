function Parser()
{
    var operators = [
        { sign: '+', precedence: 2 },
        { sign: '-', precedence: 2 },
        { sign: '*', precedence: 3 },
        { sign: '/', precedence: 3 },
        { sign: '(', precedence: 1 }
    ];
    
    var tokens = [];
    var opstack = [];
    var output = [];
    
    /**
     * Parses input using Reverse Polish Notation (Postfix).
     */
    this.parse = function(input)
    {
        tokens = input.split('').filter(elem => elem !== ' ');
        
        while(tokens.length > 0)
        {
            var token = extractToken(tokens);
    
            if(this.isOperand(token))
            {
                output.push(token);
            }
            else if (token === '(')
            {
                opstack.push(token);
            }
            else if (token === ')')
            {
                // Move all operators between () to output.
                while(opstack.length > 0)
                {
                    var currentOperator = opstack.pop();
                    if(currentOperator === '(')
                        break;
    
                    output.push(currentOperator);
                }
            }
            else if (this.isOperator(token))
            {
                var operator = this.getOperator(token);
                var currentOpstackOperator = this.getOperator(opstack[opstack.length - 1]);
                // Move all consecutive operators with higher precedence to output.
                while(opstack.length > 0 && currentOpstackOperator.precedence >= operator.precedence)
                {
                    opstack.pop();
                    output.push(currentOpstackOperator.sign);
                    currentOpstackOperator = this.getOperator(opstack[opstack.length - 1]);
                }
                opstack.push(operator.sign);
            }
            else
            {
                console.log("NOT SUPPORTED TOKEN: " + token);
            }
        }
    
        while(opstack.length > 0)
        {
            var value = opstack.pop();
            output.push(value);
        }
    
        return output.toString();
    }
    
    this.isOperand = function(token)
    {
        return token.match(/[0-9a-zA-Z]/i);
    }
    
    this.isOperator = function(token)
    {
        return operators.some(op => op.sign === token);
    }
    
    this.getOperator = function(token)
    {
        return operators.find(op => op.sign === token);
    }

    function extractToken(value)
    {
        var token = '';
        while(isNumber(value[0]))
        {  
            token += value[0];
            value.splice(0, 1);
        }

        // Not a number.
        if(token === '')
        {
            token += value[0];
            value.splice(0, 1);
        }

        return token;
    }

    function isNumber(value)
    {
        return value.match(/[0-9]/i);
    }
}