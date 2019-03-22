//
//  Taxable.h
//  intra
//
//  Created by Martine Bellaiche on 2019-03-05.
//  Copyright © 2019 Martine Bellaiche. All rights reserved.
//

#ifndef TAXABLE_H
#define TAXABLE_H
class Taxable
{
public:
    virtual void setTaxe () = 0;
    virtual double getTaxe()const = 0;
    virtual ~Taxable() = default; //besoin d'un destructeur virtuel pour delete le bon element dans le vector de Taxable* dans le main
};

#endif /* Taxable_h */
