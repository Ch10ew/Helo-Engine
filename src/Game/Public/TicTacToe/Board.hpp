#ifndef TTT_BOARD_HPP
#define TTT_BOARD_HPP

#include <cstdint>
#include <utility>
#include <vector>

namespace ttt
{
    /**
     * @brief Represents a piece on a board. Can be either None, X or O.
     */
    enum class Piece
    {
        None = 0,
        X = 88,
        O = 79,
    };

    /**
     * @brief Represents a state of a board, whether it is still in progress or not.
     */
    enum class BoardState
    {
        Playing = 0,
        Finished,
    };

    class Board
    {
    public:
        Board();
        Board(const int& width, const int& height);
        Board(const int& width, const int& height, const int& win_link_length);

        ~Board();

    public:
        const Piece& At(const int& x, const int& y) const;
        const BoardState& GetState() const;
        const Piece& GetWinner() const;
        const bool IsPlaying() const;

        void ResetBoard();
        const bool Place(const Piece& piece, const int& x, const int& y);

        void AIPlace(Piece AI_piece);

    private:
        void InitializeBoard();
        void EvaluateBoard();

    private:
        /**
         * @brief Represents a direction for a LinkInfo.
         */
        enum class Direction
        {
            Vertical,
            Horizontal,
            LeftDiagonal,
            RightDiagonal,
        };

        /**
         * @brief Struct to store info on a link of pieces. Used for AI.
         */
        struct LinkInfo
        {
            int length = 0;
            std::vector<std::pair<int, int>> pieces;
            Direction direction = Direction::Vertical;
        };

    private:
        const LinkInfo GetLongestLinkInfo() const;

    private:
        int board_width_ = 3;
        int board_height_ = 3;
        int win_link_length_ = 3;

        Piece* board_ = nullptr;
        BoardState board_state_ = BoardState::Playing;
        Piece winning_piece_ = Piece::None;
    };
} // namespace ttt

#endif // TTT_BOARD_HPP
