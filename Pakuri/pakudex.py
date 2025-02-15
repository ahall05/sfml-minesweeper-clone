from pakuri import Pakuri
class Pakudex:
    def __init__(self, capacity=20):
        self.capacity = capacity
        self.pakuris = [] # stores a list of pakuri objects
        self.size = 0

    def add_pakuri(self, species):
        # if list is full, return false
        if self.size == self.capacity:
            return False
        #check for duplicate
        else:
            for item in self.pakuris:
                #if species is in item, stop loop
                if item.get_species() == species:
                    print('Error: Pakudex already contains this species!')
                    return False

            #if loop fully executes, then species is not in self.pakuris
            self.pakuris.append(Pakuri(species))
            print('Pakuri species ' + species + ' successfully added!')
            self.size += 1
            return True


    def get_size(self):
        return self.size

    def get_capacity(self):
        return self.capacity

    def get_species_array(self):

        if len(self.pakuris) == 0:
            return None

        res = []

        for item in self.pakuris:
            res.append(item.get_species())
        return res


    def get_stats(self, species):
        for item in self.pakuris:
            # if species is in item, stop loop
            if item.get_species() == species:
                print('Species:' + species)
                print('Attack: ' + str(item.get_attack()))
                print('Defense: ' + str(item.get_defense()))
                print('Speed: ' + str(item.get_speed()))
                return

        print('Error: No such Pakuri!')

    def sort_pakuri(self):
        self.pakuris.sort()

    def evolve_species(self, species):
        for item in self.pakuris:
            if item.get_species() == species:
                item.evolve()
                return True
        print('Error: No such Pakuri!')
        return False