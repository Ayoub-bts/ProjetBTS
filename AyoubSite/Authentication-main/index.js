const express = require('express');
const path = require('path');
const session = require('express-session');
const bodyParser = require('body-parser');
const bcrypt = require('bcryptjs');
const connexion = require('./db'); 

const app = express();
const port = 8080 | 3000;
const blue = '\x1B[34m';
const red = '\x1B[31m';
const yellow = `\x1B[33m`;
const reset = `\x1B[39m`;

// Middleware pour parser les données POST
app.use(bodyParser.urlencoded({ extended: true }));

// Utiliser express-session pour gérer les sessions utilisateur
app.use(session({
    secret: 'Secret', //! clé secrète à changer
    resave: false,
    saveUninitialized: true,
    cookie: { secure: false }  //! À changer à true si vous utilisez HTTPS
}));

// Servir des fichiers statiques (CSS, JS, images, etc.)
app.use(express.static(path.join(__dirname, 'public')));

// Route pour afficher la page d'accueil (index.html)
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});


// Route de Login
app.post('/login', (req, res) => {
    const { email, password } = req.body;

    // Requête SQL pour récupérer l'utilisateur par email
    connexion.query("SELECT * FROM users WHERE email = ?", [email], async (err, result, fields) => {
        if (err) {
            console.error(`[Erreur] Erreur SQL :`, err);
            return res.status(500).send('Erreur serveur');
        }

        const user = result[0]; // ou result.rows[0] si tu utilises PostgreSQL

        // Vérifie si l'utilisateur existe
        if (!user) { return res.sendFile(path.join(__dirname, 'public', 'index.html')); }

        // Vérifie le mot de passe
        const isPasswordCorrect = await bcrypt.compare(password, user.password);
        if (!isPasswordCorrect) { return res.sendFile(path.join(__dirname, 'public', 'index.html')); }

        // Authentification réussie
        req.session.user = { id: user.id, email: user.email };
        if(!req.session.user) { return res.sendFile(path.join(__dirname, 'public', 'index.html')); }
        res.redirect('/protected');
    });
});

// Route d'inscription (signup)
app.post('/signup', async (req, res) => {
    const { names, surnames, email, password } = req.body;

    try {
        const hashedPassword = await bcrypt.hash(password, 10);

        // Insérer l'utilisateur dans la base de données avec le mot de passe hashed
        connexion.query(
            'INSERT INTO connexion.users (names, surnames, email, password) VALUES (?, ?, ?, ?)',
            [names, surnames, email, hashedPassword]
        );

        // Rediriger vers la page de login après inscription
        res.redirect('/');
    } catch (err) {
        console.error(`${red}[Erreur]${reset} Erreur durant l'inscription : `,err);
        res.status(500).send('Erreur lors de l\'inscription');
    }
});

// Route protégée, accessible après connexion
app.get('/protected', (req, res) => {
    // Si l'utilisateur n'est pas connecté
    if (!req.session.user) { return res.redirect('/'); }

    // Retourne le fichier Welcome.html du dossier public
    return res.sendFile(path.join(__dirname, 'public', 'site.html'), { errorMessage: 'Nom d\'utilisateur ou mot de passe incorrect' });
    // res.send('Page protégée. Bienvenue, ' + req.session.user.email); // Retourne un message avec l'email de l'utilisateur
});

// Route de déconnexion
app.get('/logout', (req, res) => {
    req.session.destroy((err) => {
        if (err) {
            return res.status(500).send('Erreur lors de la déconnexion');
        }
        res.redirect('/');
    });
});

app.get('/donnees', (req, res) => {
    try {
        connexion.query('SELECT valeur FROM `température`', (err, results, fields) => {
        if (err) throw err;
            // console.log(results);

            res.json(results);
        }); 
    } catch (err) {
        console.log(err);
    }

    
});

// Lancer le serveur
app.listen(port,'0.0.0.0', () => {
    connexion.connect((err) => {
        if (err) {
            console.error(`${red}[ERREUR]${reset} Erreur de connexion à la BDD : `, err);
        } else {
            console.log(`${yellow}[DB]${reset} Connexion à la base de données réussie !`);
        }
    });
    console.log(`${blue}[SITE API]${reset} Serveur en cours d'exécution sur http://localhost:${port}`);
});

