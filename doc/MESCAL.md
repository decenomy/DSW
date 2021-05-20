_(Draft)_

**MESCAL - Minimalistically Envisioned Smart Contract Assembling Language** 

A JSON formatted language proposal for Smart Contracts for Decenomy coins

**Why a new format?**
1. Why not?
2. A new format for a simple to use and minimalist pseudo programming language is needed to KISS.
3. Because.
4. A new format that serves a single specific purpose: Create Smart contracts without knowing how to write a programming language code.


**Why JSON:**
*   JSON is easy to parse, manipulate and create. 
*   Many Programming Languages support JSON natively. 
*   Arrays can be used natively in a JSON object.
*   Any JSON object element can be used as a variable.
*   Any JSON object can be interpreted as a function.
*   If MESCAL evolves in a more complex structure, JSON objects can easily define classes.

**Specifications**
*   Elements in an array object are order sensitive. Array elements will be interpreted starting from first element to the last element.
*   Elements in an JSON object are order sensitive. JSON object elements will be interpreted starting from first element to the last element.
more specifications ...


<span style="text-decoration:underline;">Some Examples:</span>


```Javascript

// MESCAL representation of MESCAL
language MESCAL {
    "types": ["basic", "condition", "contract", ...],
    "roles": ["check-signature-verification", "number", "hash160", "multi-signature", "lock-time", ...]
}


// Example: CHECKSIGVERIFY
// CScript: <pubkey> CHECKSIGVERIFY
basic My-Check-Signature-Verification {
    "type": "basic", // Optional
    "name": "My-Check-Signature-Verification", // Optional
    "role": "check-signature-verification",
    "inputs": [
        {
            "type": "pubkey",
            "name": "Pubkey",
            "value": "<pubkey>", // signature
        },
    ],
}


// Example: Number
// CScript: <any number>
basic My-Any-Number {
    "type": "basic", // Optional
    "role": "number",
    "name": "My-Any-Number", // Optional
    "inputs": [
        {
            "type": "number",
            "name": "Number",
            "value": "<any number>", // number
        },
    ],
}


// Example: Number
// CScript: 1
basic My-Number-1 {
    "type": "basic", // Optional
    "role": "number",
    "name": "My-Number-1", // Optional
    "inputs": [
        {
            "type": "number",
            "name": "Number",
            "value": 1, // number
        },
    ],
}


// Example: Number
// CScript: 2
basic My-Number-2 {
    "type": "basic", // Optional
    "role": "number",
    "name": "My-Number-2", // Optional
    "inputs": [
        {
            "type": "number",
            "name": "Number",
            "value": 2, // number
        },
    ],
}


// Example: HASH160
// CScript: HASH160 <Hash160(<any string or number>)>
basic My-Hash160 {
    "type": "basic", // Optional
    "role": "hash160",
    "name": "My-Hash160", // Optional
    "inputs": [
        {
            "type": "string-or-number",
            "name": "String-or-Number-to-Hash",
            "value": "<any string or number>", // string or number to be hashed
        },
    ],
}


// Example: m of n Multi Signature contract
// CScript: <pubkey 1> <pubkey 2> 2 CHECKMULTISIG
basic My-Multi-Signature {
    "type": "basic", // Optional
	"role": "multi-signature",
    "name": "My-Multi-Signature", // Optional
    "inputs": [
        {
            "type": "number",
            "name": "n",
            "value": 2,
        },
        {
            "type": "number",
            "name": "m",
            "value": 2,
        },
        {
            "type": "array",
            "name": "Signatures",
            "value": [
                "<Pubkey 1>",
                // More signatures up to n
                "<Pubkey n>",
            ],
        },
    ],
}


// Example: Time Locked contract (nLockTime, CheckLockTimeVerify - BIP65, "Relative locktime"/nSequence - BIP68/112/113, CheckSequenceVerify - BIP68/112/113)
// CScript: <expiry time> CHECKLOCKTIMEVERIFY DROP
basic My-Lock-Time {
    "type": "basic", // Optional
	"role": "lock-time",
    "name": "My-Lock-Time", // Optional
	"inputs": [
        {
            "type": "timestamp-or-block-height",
            "name": "Lock-Until",
            "value": 1620872586, // timestamp or block height of the time until the funds are kept locked
        },
    ],
}

// Example: If Condition
// CScript: IF-ELSE-ENDIF
condition My-If-Condition {
    "type": "condition", // Optional
    "role": "if-condition",
    "name": "My-If-Condition", // Optional
    "true": [
        {
            "required": true,
            "type": "basic", // Optional if the name is unique
            "name": "My-Lock-Time", // all the inputs are given in the basic json object declaration.
        },
        {
            "required": true,
            "type": "basic", // Optional if the name is unique
            "name": "My-Check-Signature-Verification", // all the inputs are given in the basic json object declaration.
        },
        {
            "required": true,
            "type": "basic",
            "name": "My-Number-1",
        },
    ],
    "false": [
        {
            "required": true,
            "type": "basic",
            "name": "My-Number-2",
        },
    ],
}

// Example: A complex Smart Contract
contract My-Example-Contract {
    "type": "contract", // Optional
    "description": "The contract description. Shouldn't be very long.", // Optional
    "name": "My-Contract", // Optional
    "actions": [
        {
            "type": "condition",
            "name": "My-If-Condition",
            "role": "if-condition", // Optional
        },
        {
            "type": "basic",
            "name": "My-Multi-Signature",
            // "role": "multi-signature",
        },
    ]
}


// Example: Freezing Funds
// CScript: <expiry time> CHECKLOCKTIMEVERIFY DROP DUP HASH160 <pubKeyHash> EQUALVERIFY CHECKSIG
contract Freezing-Funds {
    "type": "contract",
    "description": "Freezes funds in a UTXO until a certain time.", // Optional
    "name": "Freezing-Funds", // Optional
    "actions": [
        {
            "type": "basic",
            "name": "My-Lock-Time",
        },
        {
            "type": "basic",
            "name": "My-Hash160",
        },
        {
            "type": "basic",
            "name": "My-Check-Signature-Verification",
        },
    ],
}

```
