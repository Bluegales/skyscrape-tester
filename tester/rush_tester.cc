//#include <experimental/algorithm>
#include <bit>
#include <cinttypes>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

#include <string.h>

std::string output;

extern "C" {
  extern int captured_main(int argc, char **argv);

  size_t write(int fd, const void* buf, size_t n) {
    output.append((char *)buf, n);
    return 0;
  }
}

// void printCase(Testcase t) {
//   std::cout << "   " << t.input.substr(0, 7) << "\n\n";
//   for (int i = 0; i < 4; i++) {
//     std::cout << t.input.substr(16 + 2 * i,1) << "  ";
//     std::cout << t.board.substr(i * 8, 7) << "  ";
//     std::cout << t.input.substr(24 + 2 * i, 1) << "\n";
//   }
//   std::cout << "\n   " << t.input.substr(8, 7) << "\n\n";
// }

std::string getInput(uint32_t board) {
  std::string input;
  auto getHeight = [&board](int position){
    return (board >> (position * 2)) & 0b11;
  };
  auto visibleCount = [&board, &getHeight](int start, int position_offset){
    int visible = 1;
    int height = getHeight(start);
    for (int i = 0; i < 3; i++) {
      start += position_offset;
      if (getHeight(start) > height) {
        height = getHeight(start);
        visible++;
      }   
    }
    return visible;
  };
  for (int i = 0; i < 4; i++) {
    input.push_back(visibleCount(i, 4) + '0');
    input.push_back(' ');
  }
  for (int i = 0; i < 4; i++) {
    input.push_back(visibleCount(12 + i, -4) + '0');
    input.push_back(' ');
  }
  for (int i = 0; i < 4; i++) {
    input.push_back(visibleCount(i * 4, 1) + '0');
    input.push_back(' ');
  }
  for (int i = 0; i < 4; i++) {
    input.push_back(visibleCount(i * 4 + 3, -1) + '0');
    input.push_back(' ');
  }
  input.pop_back();
  return input;
}

std::string boardString(uint32_t board) {
  std::string board_string;
  for (int i = 0; i < 16; i++) {
    int mask = (board >> (i * 2)) & 0b11;
    board_string.push_back(mask + '1');
    if (i % 4 == 3)
      board_string.push_back('\n');
    else
      board_string.push_back(' ');
  }
  return board_string;
}

void recursiveBoard(std::unordered_map<std::string, std::vector<std::string>> &cases, uint32_t board, uint64_t remaining, int position) {
  if (position == 16) {
    std::string input_str = getInput(board);
    std::string board_str = boardString(board);
    auto it = cases.find(input_str);
    if (it == cases.end()) {
      cases.insert({input_str, {boardString(board)}});
    } else {
      it->second.push_back(boardString(board));
    }
    return;
  }
  int pos_remaining = (remaining >> position * 4) & 0b1111;
  if (pos_remaining == 0) return;
  for (int i = 0; i < 4; i++) {
    uint64_t number_mask = 0b1 << i;
    if (pos_remaining & number_mask) {
      uint32_t new_board = board | (i << (position * 2));
      uint64_t new_remaining = remaining;
      int row = (position / 4);
      int column = (position % 4);
      for (int j = 0; j < 4; j++) {
        new_remaining &= ~(number_mask << (((row * 4) + j) * 4));
        new_remaining &= ~(number_mask << ((column + (j * 4)) * 4));  
      }
      recursiveBoard(cases, new_board, new_remaining, position + 1);
    }
  }
}

void test(std::string input_str, std::vector<std::string> outputs) {
  output.clear();
  char *program_name = strdup("rush");
  char *input = strdup(input_str.c_str());
  char *argv[2] = {program_name, input};
  captured_main(2, argv);
  for (auto it = outputs.begin(); it != outputs.end(); it++) {
    if (output == *it) {
      return;
    }
  }
  std::cout << "=====================\nERROR: wrong answer:\n\n";
  std::cout << "input:\n--" << input_str << "--\n";
  std::cout << "expected:\n";
  //printCase(test_case);
  std::cout << "got:\n" << output << "\n";
  free(program_name);
  free(input);
}

int main() {
  std::unordered_map<std::string, std::vector<std::string>> test_cases;
  recursiveBoard(test_cases, 0, UINT64_MAX, 0);
  // auto test = [&test_cases](int id) {
  //   char *program_name = strdup("rush");
  //   char *input = strdup(test_cases[id].input.c_str());
  //   char *argv[2] = {program_name, input};
  //   captured_main(2, argv);
  // };
  //printCase(test_cases[0]);
  for (auto it = test_cases.begin(); it != test_cases.end(); it++) {
    test(it->first, it->second);
  }
  //test(test_cases[0]);
}
