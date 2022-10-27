#include "TicTacToe/Board.hpp"

#include "TicTacToe/Util.hpp"

#include <cstdint>
#include <cstdlib>
#include <ctime>

namespace ttt
{
    /**
     * @brief Construct a new Board:: Board object.
     */
    Board::Board()
    {
        InitializeBoard();
    }

    /**
     * @brief Construct a new Board:: Board object.
     *
     * @param width Board width.
     * @param height Board height.
     */
    Board::Board(const int& width, const int& height) : board_width_(width),
                                                        board_height_(height)
    {
        InitializeBoard();
    }

    /**
     * @brief Construct a new Board::Board object.
     *
     * @param width Board width.
     * @param height Board height.
     * @param win_link_length Length of the link/chain to be considered a win. Default is 3.
     */
    Board::Board(const int& width, const int& height, const int& win_link_length) : board_width_(width),
                                                                                    board_height_(height),
                                                                                    win_link_length_(win_link_length)
    {
        InitializeBoard();
    }

    /**
     * @brief Destroy the Board::Board object.
     *
     * Cleans up the board (dynamic array).
     */
    Board::~Board()
    {
        delete[] board_;
    }

    /**
     * @brief Gets the piece at the given coordinates.
     *
     * @param x x position.
     * @param y y position.
     * @return const Piece& Piece at the given coordinates. Pieces available are Piece::None, Piece::X, Piece::O.
     */
    const Piece& Board::At(const int& x, const int& y) const
    {
        return board_[y * board_width_ + x];
    }

    /**
     * @brief Gets the state of the board.
     *
     * States available are BoardState::Playing and BoardState::Finished.
     *
     * @return const BoardState& State of the board.
     */
    const BoardState& Board::GetState() const
    {
        return board_state_;
    }

    /**
     * @brief Gets the winning piece.
     *
     * @return const Piece& Piece that won.
     */
    const Piece& Board::GetWinner() const
    {
        return winning_piece_;
    }

    /**
     * @brief Gets if the board is still in the Playing (BoardState::Playing) state.
     *
     * @return true The board state is BoardState::Playing.
     * @return false The board state is not BoardState::Playing.
     */
    const bool Board::IsPlaying() const
    {
        return (board_state_ == BoardState::Playing);
    }

    /**
     * @brief Resets the board state.
     */
    void Board::ResetBoard()
    {
        // Reset board pieces
        for (int i = 0; i < board_width_ * board_height_; ++i)
            board_[i] = Piece::None;

        board_state_ = BoardState::Playing;
        winning_piece_ = Piece::None;
    }

    /**
     * @brief Places a piece at the given coordinates.
     *
     * @param piece Piece type.
     * @param x x position.
     * @param y y position.
     * @return true Piece is placed successfully.
     * @return false Failed to place piece.
     */
    const bool Board::Place(const Piece& piece, const int& x, const int& y)
    {
        // Checks before placing piece
        if (board_state_ == BoardState::Finished)
            return false;
        if (piece == Piece::None)
            return false;
        if (x >= board_width_)
            return false;
        if (y >= board_height_)
            return false;
        if (board_[y * board_width_ + x] != Piece::None)
            return false;

        // Place the piece
        board_[y * board_width_ + x] = piece;

        // Determine any wins
        EvaluateBoard();

        return true;
    }

    /**
     * @brief Get the AI to place a piece of the given piece type.
     *
     * @param AI_piece AI's piece type. Either Piece::X or Piece::O.
     */
    void Board::AIPlace(Piece AI_piece)
    {
        // Try blocking/placing if 1 away from winning
        LinkInfo longest_link = GetLongestLinkInfo();
        int (*operation_x)(int) = Util::DoNothing;
        int (*operation_x_inverse)(int) = Util::DoNothing;
        int (*operation_y)(int) = Util::DoNothing;
        int (*operation_y_inverse)(int) = Util::DoNothing;
        switch (longest_link.direction)
        {
        case Direction::Horizontal:
            operation_x = Util::Add1;
            operation_x_inverse = Util::Sub1;
            break;
        case Direction::Vertical:
            operation_y = Util::Add1;
            operation_y_inverse = Util::Sub1;
            break;
        case Direction::LeftDiagonal:
            operation_x = Util::Sub1;
            operation_x_inverse = Util::Add1;
            operation_y = Util::Sub1;
            operation_y_inverse = Util::Add1;
            break;
        case Direction::RightDiagonal:
        default:
            operation_x = Util::Add1;
            operation_x_inverse = Util::Sub1;
            operation_y = Util::Add1;
            operation_y_inverse = Util::Sub1;
            break;
        }

        if (longest_link.length == board_width_ - 1 || longest_link.length == board_height_ - 1)
        {
            // Try placing by offset 1 of last piece
            if (this->Place(
                    AI_piece,
                    operation_x(longest_link.pieces.back().first),
                    operation_y(longest_link.pieces.back().second)))
            {
                return;
            }

            // Try placing by offset 1 of first piece
            if (this->Place(
                    AI_piece,
                    operation_x(longest_link.pieces.front().first),
                    operation_y(longest_link.pieces.front().second)))
            {
                return;
            }
        }

        // Try placing center
        if (this->Place(AI_piece, board_width_ / 2, board_height_ / 2))
            return;

        // Try placing corners
        if (this->Place(AI_piece, 0, 0))
            return;
        if (this->Place(AI_piece, 0, board_height_ - 1))
            return;
        if (this->Place(AI_piece, board_width_ - 1, 0))
            return;
        if (this->Place(AI_piece, board_width_ - 1, board_height_ - 1))
            return;

        // Try placing somewhere random :")
        srand(time(0)); // Seed PRNG
        while (!this->Place(AI_piece, (rand() % board_width_) - 1, (rand() % board_height_) - 1))
        {
            // Do nothing, because the while condition already performs what we need
        }
    }

    /**
     * @brief Initializes the dynamic array that will store the board's data based on the variables.
     */
    void Board::InitializeBoard()
    {
        board_ = new Piece[board_height_ * board_width_]();
    }

    /**
     * @brief Evaluates the board to see if there is a winner.
     */
    void Board::EvaluateBoard()
    {
        for (int y = 0; y < board_height_; ++y)
        {
            for (int x = 0; x < board_width_; ++x)
            {
                int i = 1;
                Piece current = board_[y * board_width_ + x];
                if (current != Piece::None)
                {
                    // Check down
                    for (i = 1; i <= win_link_length_; ++i)
                    {
                        if (y + i >= board_height_)
                            break;

                        if (board_[(y + i) * board_width_ + (x)] != current)
                            break;
                    }
                    if (i == win_link_length_)
                    {
                        board_state_ = BoardState::Finished;
                        winning_piece_ = current;
                        return;
                    }

                    // Check right
                    for (i = 1; i <= win_link_length_; ++i)
                    {
                        if (x + i >= board_width_)
                            break;

                        if (board_[y * board_width_ + (x + i)] != current)
                            break;
                    }
                    if (i == win_link_length_)
                    {
                        board_state_ = BoardState::Finished;
                        winning_piece_ = current;
                        return;
                    }

                    // Check bottom left
                    for (i = 1; i <= win_link_length_; ++i)
                    {
                        if (y - i < 0 || x - i < 0)
                            break;

                        if (board_[(y - i) * board_width_ + (x - i)] != current)
                            break;
                    }
                    if (i == win_link_length_)
                    {
                        board_state_ = BoardState::Finished;
                        winning_piece_ = current;
                        return;
                    }

                    // Check bottom right
                    for (i = 1; i <= win_link_length_; ++i)
                    {
                        if (y + i >= board_height_ || x + i >= board_width_)
                            break;

                        if (board_[(y + i) * board_width_ + (x + i)] != current)
                            break;
                    }
                    if (i == win_link_length_)
                    {
                        board_state_ = BoardState::Finished;
                        winning_piece_ = current;
                        return;
                    }
                }
            }
        }
    }

    /**
     * @brief Gets info on the longest link on the board. For AI use.
     *
     * @return const Board::LinkInfo Link info for the longest link on the board.
     */
    const Board::LinkInfo Board::GetLongestLinkInfo() const
    {
        LinkInfo longest_link;
        for (int y = 0; y < board_height_; ++y)
        {
            for (int x = 0; x < board_width_; ++x)
            {
                int i = 1;

                Piece current = board_[y * board_width_ + x];
                if (current != Piece::None)
                {
                    // Check down
                    for (i = 1; i <= win_link_length_; ++i)
                    {
                        if (y + i >= board_height_)
                            break;

                        if (board_[(y + i) * board_width_ + (x)] != current)
                            break;
                    }
                    if (i > longest_link.length)
                    {
                        longest_link.length = i;
                        longest_link.pieces.clear();
                        for (i = 1; i <= longest_link.length; ++i)
                        {
                            longest_link.pieces.push_back(
                                std::pair<int, int>(y + i, x));
                        }
                    }

                    // Check right
                    for (i = 1; i <= win_link_length_; ++i)
                    {
                        if (x + i >= board_width_)
                            break;

                        if (board_[y * board_width_ + (x + i)] != current)
                            break;
                    }
                    if (i > longest_link.length)
                    {
                        longest_link.length = i;
                        longest_link.pieces.clear();
                        for (i = 1; i <= longest_link.length; ++i)
                        {
                            longest_link.pieces.push_back(
                                std::pair<int, int>(y, x + i));
                        }
                    }

                    // Check bottom left
                    for (i = 1; i <= win_link_length_; ++i)
                    {
                        if (y - i < 0 || x - i < 0)
                            break;

                        if (board_[(y - i) * board_width_ + (x - i)] != current)
                            break;
                    }
                    if (i > longest_link.length)
                    {
                        longest_link.length = i;
                        longest_link.pieces.clear();
                        for (i = 1; i <= longest_link.length; ++i)
                        {
                            longest_link.pieces.push_back(
                                std::pair<int, int>(y - i, x - i));
                        }
                    }

                    // Check bottom right
                    for (i = 1; i <= win_link_length_; ++i)
                    {
                        if (y + i >= board_height_ || x + i >= board_width_)
                            break;

                        if (board_[(y + i) * board_width_ + (x + i)] != current)
                            break;
                    }
                    if (i > longest_link.length)
                    {
                        longest_link.length = i;
                        longest_link.pieces.clear();
                        for (i = 1; i <= longest_link.length; ++i)
                        {
                            longest_link.pieces.push_back(
                                std::pair<int, int>(y + i, x + i));
                        }
                    }
                }
            }
        }
        return longest_link;
    }
} // namespace ttt
