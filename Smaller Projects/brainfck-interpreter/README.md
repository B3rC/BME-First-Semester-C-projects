# Brainfuck Interpreter in C

This is a simple Brainfuck interpreter written in C. It reads Brainfuck code, executes it, and prints the output to the console. The program also includes a syntax check for unmatched brackets (`[` and `]`).

## Features

- **Syntax Validation**: Ensures that all brackets in the Brainfuck code are correctly paired.
- **Memory Tape Simulation**: A memory tape of 32,768 cells is simulated, allowing for proper Brainfuck program execution.
- **Basic Brainfuck Commands Supported**: The following Brainfuck commands are supported:
  - `>`: Increment memory pointer
  - `<`: Decrement memory pointer
  - `+`: Increment value at memory cell
  - `-`: Decrement value at memory cell
  - `.`: Output value at memory cell as a character
  - `,`: Input a character into the current memory cell
  - `[`: Jump forward to the matching `]` if the value at the current memory cell is 0
  - `]`: Jump back to the matching `[` if the value at the current memory cell is non-zero

  ## Example output when running the Sierpinski triangle program

                                *
                               * *
                              *   *
                             * * * *
                            *       *
                           * *     * *
                          *   *   *   *
                         * * * * * * * *
                        *               *
                       * *             * *
                      *   *           *   *
                     * * * *         * * * *
                    *       *       *       *
                   * *     * *     * *     * *
                  *   *   *   *   *   *   *   *
                 * * * * * * * * * * * * * * * *
                *                               *
               * *                             * *
              *   *                           *   *
             * * * *                         * * * *
            *       *                       *       *
           * *     * *                     * *     * *
          *   *   *   *                   *   *   *   *
         * * * * * * * *                 * * * * * * * *
        *               *               *               *
       * *             * *             * *             * *
      *   *           *   *           *   *           *   *
     * * * *         * * * *         * * * *         * * * *
    *       *       *       *       *       *       *       *
   * *     * *     * *     * *     * *     * *     * *     * *
  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
