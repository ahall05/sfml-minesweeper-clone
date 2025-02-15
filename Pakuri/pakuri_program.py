from pakuri import Pakuri
from pakudex import Pakudex

if __name__ == '__main__':
    class LessThanZeroError(Exception):
        def __init__(self, value):
            self.value = value


    print('Welcome to Pakudex: Tracker Extraordinaire!')

    #initialize capacity to enter while loop
    capacity = -1
    while capacity < 0:
        try:
            capacity = int(input('Enter max capacity of the Pakudex: '))
            if capacity < 0:
                raise LessThanZeroError('Please enter a valid size.')
        except ValueError:
            print('Please enter a valid size.')
        except LessThanZeroError:
            print('Please enter a valid size.')





    print('The Pakudex can hold ' + str(capacity) + ' species of Pakuri.')

    pakudex = Pakudex(capacity)
    done = False

    while not done:
        print('''\nPakudex Main Menu
-----------------
1. List Pakuri
2. Show Pakuri
3. Add Pakuri
4. Evolve Pakuri
5. Sort Pakuri
6. Exit\n''')

        #check for valid input
        try:
            choice = int(input("What would you like to do? "))
        except ValueError:
            print('Unrecognized menu selection!')
            continue
        #check for valid menu selection
        if 0 < choice < 7:
            match choice:
                case 1:
                    if(pakudex.size != 0):
                        print('Pakuri In Pakudex:')
                        i = 1
                        for item in pakudex.get_species_array():
                            print(i, end='. ')
                            print(item)
                            i += 1
                    else:
                        print('No Pakuri in Pakudex yet!')
                case 2:
                        species = input('Enter the name of the species to display: ')
                        pakudex.get_stats(species)
                        #
                case 3:
                    if not pakudex.size == capacity:
                        species = input('Enter the name of the species to add: ')
                        pakudex.add_pakuri(species)
                    else:
                        print('Error: Pakudex is full!')


                case 4:
                    print('Enter the name of the species to evolve: ', end='')
                    species = input()
                    pakudex.evolve_species(species)

                case 5:
                    pakudex.sort_pakuri()
                    print('Pakuri have been sorted!')
                case 6:
                    print('Thanks for using Pakudex! Bye!')
                    done = True
        else:
            print('Unrecognized menu selection!')