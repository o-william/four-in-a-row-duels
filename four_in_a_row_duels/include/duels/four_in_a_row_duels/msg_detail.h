// generated from four_in_a_row_duels.yaml -- editing this file by hand is not recommended
inline std::ostream& operator<<(std::ostream& ss, const duels::four_in_a_row_duels::Cell &cell)
{
  ss << "{";
  ss << "row: " << cell.row << ',';
  ss << "column: " << cell.column << ',';
  ss << "player: " << cell.player << "}";
  return ss;
}
