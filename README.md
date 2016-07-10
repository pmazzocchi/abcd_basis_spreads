# The ABCD of Interest Rate Basis Spreads
F.M. Ametrano, L. Ballabio, P. Mazzocchi

Presented at QuantLib User Meeting, London, July 12, 2016

- Working Paper: http://ssrn.com/abstract=2696743
- GitHub: https://github.com/paolomazzocchi/abcd_basis_spreads
- Speaker Deck: https://speakerdeck.com/nando1970/the-abcd-of-interest-rate-basis-spreads

We show that forward rates can be modeled as abcd parametric tenor basis spreads over the underlying overnight rate curve. This is possible for both continuously and simply compounded forward rates, with a simple approximation for converting between the corresponding basis. Increasing interest-rate tenor dominance, as empirically observed, is recovered and can be structurally enforced using a robust methodology improvement based on relative basis between the most liquid tenors. The smoothness requirement is moved from forward rate curves to tenor basis curves, properly dealing with the market evidence of jumps in forward rates. In the case of continuously compounded tenor basis, pseudo-discount factors are also available. An implementation of this methodology is available in the QuantLib open-source project.
