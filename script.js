/* Constants for board dimensions */
const ROWS = 6;
const COLS = 7;
let currentPlayer = 'red'; 
let board = [];

/**
 * Initializes the game board data and visual elements
 */
function createBoard() {
    const boardElement = document.getElementById('board');
    boardElement.innerHTML = ''; // Clear previous board
    
    // Initialize 2D array with null values
    board = Array(ROWS).fill().map(() => Array(COLS).fill(null));

    // Create visual cells
    for (let r = 0; r < ROWS; r++) {
        for (let c = 0; c < COLS; c++) {
            const cell = document.createElement('div');
            cell.classList.add('cell');
            cell.dataset.row = r;
            cell.dataset.col = c;
            // Add click event to handle moves
            cell.addEventListener('click', () => makeMove(c));
            boardElement.appendChild(cell);
        }
    }
}

/**
 * Handles the logic of placing a disc in a column
 */
function makeMove(col) {
    // Find the lowest empty row in the selected column
    for (let r = ROWS - 1; r >= 0; r--) {
        if (!board[r][col]) {
            board[r][col] = currentPlayer;
            updateUI();
            
            // Check if the current move wins the game
            if (checkWin(r, col)) {
                setTimeout(() => {
                    alert("Game Over! " + (currentPlayer === 'red' ? 'Red' : 'Yellow') + " Wins!");
                    resetGame();
                }, 100);
                return;
            }
            
            // Switch turns
            currentPlayer = (currentPlayer === 'red') ? 'yellow' : 'red';
            document.getElementById('current-player-name').innerText = (currentPlayer === 'red' ? 'Red' : 'Yellow');
            return;
        }
    }
}

/**
 * Updates the visual display of the board based on the board array
 */
function updateUI() {
    const cells = document.querySelectorAll('.cell');
    cells.forEach(cell => {
        let r = cell.dataset.row;
        let c = cell.dataset.col;
        if (board[r][c] === 'red') cell.classList.add('red');
        if (board[r][c] === 'yellow') cell.classList.add('yellow');
    });
}

/**
 * Checks all directions for 4-in-a-row
 */
function checkWin(r, c) {
    function checkDirection(dr, dc) {
        let count = 1;
        // Check in one direction
        let row = r + dr, col = c + dc;
        while (row >= 0 && row < ROWS && col >= 0 && col < COLS && board[row][col] === currentPlayer) {
            count++; row += dr; col += dc;
        }
        // Check in opposite direction
        row = r - dr; col = c - dc;
        while (row >= 0 && row < ROWS && col >= 0 && col < COLS && board[row][col] === currentPlayer) {
            count++; row -= dr; col -= dc;
        }
        return count >= 4;
    }
    // Vertical, Horizontal, and both Diagonals
    return checkDirection(0, 1) || checkDirection(1, 0) || checkDirection(1, 1) || checkDirection(1, -1);
}

/**
 * Resets the game to its initial state
 */
function resetGame() {
    currentPlayer = 'red';
    document.getElementById('current-player-name').innerText = 'Red';
    createBoard();
}

// Start the game on page load
createBoard();