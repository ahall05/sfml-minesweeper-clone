class Pakuri:
    def __init__(self, species):
        self.species = str(species)
        self.attack = (len(species) * 7) + 9
        self.defense = (len(species) * 5) + 17
        self.speed = (len(species) * 6) + 13
    #getters and setters
    def get_species(self):
        return self.species

    def get_attack(self):
        return self.attack
    def get_speed(self):
        return self.speed

    def get_defense(self):
        return self.defense

    def set_species(self, new_species):
        self.species = new_species

    def set_attack(self, attack):
        self.attack = attack

    def set_defense(self, defense):
        self.defense = defense

    def set_speed(self, speed):
        self.speed = speed

    def evolve(self):
        self.attack = self.attack * 2
        self.defense = self.defense * 4
        self.speed = self.speed * 3
        print(self.species + 'has evolved!')

    def __lt__(self, other):

        return self.species < other.species


        # for i in range(len(self.species)):
        #     if self.species[i] > other.species[i]:
        #         return self.species
        #     else:
        #         return other.species