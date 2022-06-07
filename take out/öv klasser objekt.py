class Persondata:
        def _init_(self, namn = 'NN', adress = 'Okänd',
                   telefon = '-', saldo = 0):
            self.namn = namn
            self.adr = adress
            self.tel = telefon
            self.saldo = saldo

        def skrivut(self):
            print('Namn: {} Adress: {} Telefon: {} Telefon: {} Saldo {:.2f}'.format (self.namn, self.adr, self.tel, self.saldo)) 
