# Carl Patterson, November 3, 2016
# This is a guessing game where the player tries to guess a random number
# chosen by the computer

import random


def display_menu():
    print('''Welcome to the guessing game {}.
          Please choose your difficulty
          1) Normal: 1-100, 8 tries.
          2) Impossible: 1-1000, 14 tries.
          3) Masochist: 1-10000, 19 tries'''.format(player_name))


def game_loop(s_num, turns=int()):
    count = 0
    print('Welcome to the guessing game {}! Please try to guess the correct '
          'number\nYou have up to {} attempts'.format(player_name, turns))

    while True:
        count += 1
        player_num = input('Enter your number: ')

        try:
            player_num = int(player_num)
        except ValueError:
            print("That is not a number, please enter a number!")
            continue

        if s_num == player_num:
            print('WOOT!!! You won! after {} attempts. Congratulations!!! '
                  '\nThank you for playing {} and '
                  'please come again.'.format(count, player_name))
            exit()
        elif count == turns:
            print("I'm sorry {} but you lost after {} attempts."
                  "\nBetter luck next time! :)".format(player_name, count))
            exit()
        elif s_num < player_num:
            print('Whoa Jr, not so high. Bring it down some')
        elif s_num > player_num:
            print('Bit low there mate. Try something higher')


def get_difficulty():
    while True:
        level = input("Enter the number corresponding to your choice: ")
        try:
            level = int(level)
            assert int(level) in range(1, 4)
        except (ValueError, AssertionError):
            print("That is not a valid choice. Options are 1, 2 or 3")
            continue

        return level


def setup_game(level=None):
    if level == 1:
        secret_num = random.randrange(1, 101)
        game_loop(secret_num, 8)

    elif level == 2:
        secret_num = random.randrange(1, 1001)
        game_loop(secret_num, 14)

    elif level == 3:
        secret_num = random.randrange(1, 10001)
        game_loop(secret_num, 19)


if __name__ == '__main__':
    player_name = input('Hello challenger! Please tell me your name: ')
    display_menu()
    setup_game(get_difficulty())
