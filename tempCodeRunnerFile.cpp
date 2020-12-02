    board[1][1] = 'X';
    board[1][2] = 'X';
    board[1][3] = 'X';
    board[1][4] = 'X';
    board[1][5] = 'X';
    cout<<GetWinner(board, 5,5)<<endl;

    for (int i = 0; i<15; i++)
    {
        for (int j = 0; j<15; j++)
        {
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
    
    cout<<endl;