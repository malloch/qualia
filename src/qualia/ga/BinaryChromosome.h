/*
 * BinaryChromosome.h
 *
 * (c) 2012 Sofian Audry -- info(@)sofianaudry(.)com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BINARYCHROMOSOME_H_
#define BINARYCHROMOSOME_H_

#include <qualia/core/common.h>
#include <qualia/util/bitarray.h>
#include <qualia/util/random.h>

#include "Chromosome.h"

#include <string.h>
//void defaultMutator(Chromosome& chromosome, float);
//void defaultInitializer(Chromosome& chromosome);

class BinaryChromosomeProperties {
public:
  /// The number of genes in the chromosome.
  unsigned int _nGenes;

  /// The size (in bits) of each gene.
  uint8_t* _geneSizes;

  /// The initializer, mutator and evaluator functions.
  Initializer initializer;
  Mutator mutator;
  Evaluator evaluator;

  BinaryChromosomeProperties(unsigned int nGenes, const uint8_t* geneSizes,
                       Initializer initializer=0, Mutator mutator=0);

  /// Returns the number of genes in the chromosome.
  unsigned int nGenes() const { return _nGenes; }

  /// Returns the size (in bits) of gene #i#.
  uint8_t geneSize(int i) const { return _geneSizes[i]; }

  /// Returns the total size (in bits) of the chromosome.
  unsigned int bitSize() const;

  /// Returns the total size (in bytes) of the chromosome.
  unsigned int byteSize() const { return ( (bitSize()+7) / 8); }

  /// Returns the bit at which gene #gene# starts.
  int getStartBitPosition(int gene) const;

  /// Tests equality.
  virtual bool equals(const BinaryChromosomeProperties& info);
};

class BinaryChromosome: public Chromosome {
public:
  BinaryChromosomeProperties* info;
  uint8_t* code;

  BinaryChromosome(BinaryChromosomeProperties* info);
  virtual ~BinaryChromosome();

  virtual void copyFrom(const Chromosome& c);

  virtual void init();
  virtual void mutate(float p);
  virtual bool equals(const Chromosome& c) const;

  /// Returns the value of gene #gene# as a 64-bit integer.
  uint64_t getGeneValue(int gene) const;

  /// Sets the value of gene #gene# to #value# (max. 64-bit).
  void setGeneValue(int gene, uint64_t value);

  // Static methods.
  static void initializeRandom(Chromosome& chromosome);

  static void mutateFlip(Chromosome& chromosome, float probability);

  static void crossoverOnePoint(const Chromosome& parent1, const Chromosome& parent2,
                                Chromosome* offspring1, Chromosome* offspring2);
  static void crossoverTwoPoint(const Chromosome& parent1, const Chromosome& parent2,
                                Chromosome* offspring1, Chromosome* offspring2);

  static void _codeCrossoverOnePoint(uint8_t* offspringCode, const uint8_t* parentCode1, const uint8_t* parentCode2,
                                     unsigned int point, unsigned int codeSize);
  static void _codeCrossoverTwoPoint(uint8_t* offspringCode, const uint8_t* parentCode1, const uint8_t* parentCode2,
                                     unsigned int point1, unsigned int point2, unsigned int codeSize);
//  virtual int compare(const Chromosome& g);
//  virtual float evaluate();

};


#endif /* BINARYCHROMOSOME_H_ */
