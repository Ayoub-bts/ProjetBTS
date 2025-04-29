# Page d'Authentification avec Express et MySQL

Ce projet est une page d'authentification réalisée avec **Node.js**, **Express**, **MySQL**, et **bcryptjs**. Il permet aux utilisateurs de se connecter et de s'inscrire via un formulaire d'authentification sécurisé. Une fois l'utilisateur authentifié, il peut accéder à des pages protégées.

## Fonctionnalités

- **Page d'inscription** : Permet à un utilisateur de créer un compte avec un mot de passe sécurisé.
- **Page de connexion** : Permet à un utilisateur de se connecter avec son email et son mot de passe.
- **Pages protégées** : Les utilisateurs connectés peuvent accéder à des pages réservées.
- **Déconnexion** : Permet à un utilisateur de se déconnecter de la session en cours.
- **Sécurisation du mot de passe** : Utilisation de la bibliothèque `bcryptjs` pour hacher les mots de passe.

## Technologies utilisées

- **Node.js** : Environnement d'exécution JavaScript côté serveur.
- **Express** : Framework pour créer des applications web avec Node.js.
- **MySQL** : Base de données relationnelle utilisée pour stocker les utilisateurs.
- **bcryptjs** : Bibliothèque permettant de hacher les mots de passe de manière sécurisée.
- **express-session** : Middleware pour gérer les sessions utilisateur et maintenir l'authentification.
- **mysql2** : Bibliothèque pour se connecter à une base de données MySQL.

## Installation

1. Clonez ce repository sur votre machine locale :
    ```bash
    git clone https://github.com/Luuxio/Authentication.git
    cd Authentication
    ```

2. Installez les dépendances du projet :
    ```bash
    npm install
    ```

3. Configurez votre base de données MySQL. Vous pouvez créer une base de données nommée `connexion` et exécuter la commande suivante pour créer la table `users` :
    ```sql
    CREATE DATABASE connexion;
    USE connexion;

    CREATE TABLE users (
        id INT AUTO_INCREMENT PRIMARY KEY,
        names VARCHAR(100),
        surnames VARCHAR(100),
        email VARCHAR(255) UNIQUE,
        password VARCHAR(255)
    );
    ```

4. Modifiez les informations de connexion à la base de données MySQL dans le fichier `database.js`, si vous n'avez pas **PostgreSQL**, vous pouvez installer **MySQL2** et désinstaller **PostgreSQL** :
    ```bash
    npm install mysql2
    npm uninstall pg
    ```

    Code pour **MySQL2**
    ```js
    const pool = mysql.createPool({
        host: 'localhost',
        user: 'root', // Votre utilisateur MySQL
        password: '', // Votre mot de passe MySQL
        database: 'connexion'
    });
    ```

5. Lancez l'application :
    ```bash
    npm run dev
    ```

6. L'application sera accessible à l'adresse suivante dans votre navigateur :
    ```
    http://localhost:3000
    ```

## HTML

Le code HTML pour les pages de connexion et d'inscription est directement inspiré de vidéos YouTube pour des démonstrations d'interface. Les fichiers HTML se trouvent dans le dossier `public` et sont utilisés pour afficher les formulaires d'authentification et les pages protégées.

- **index.html** : La page d'accueil qui contient le formulaire de connexion.
- **welcome.html** : La page affichée après une connexion réussie, avec un message de bienvenue.
- **map.html** : Une page protégée accessible uniquement aux utilisateurs connectés.

## Structure du projet

Voici la structure des fichiers du projet :
```
/authentication-page 
│ 
├── /public 
    │ 
    ├── index.html # Formulaire de connexion 
    │ 
    ├── welcome.html # Page après connexion 
    │ 
    └── map.html # Page protégée 
│ 
├── app.js # Code principal de l'application (Express) 
├── package.json # Dépendances et scripts du projet 
└── README.md # Ce fichier
```
## Auteurs

- **Luuxio_** - Créateur du projet

## License

Ce projet est sous licence MIT - voir le fichier [LICENSE](LICENSE) pour plus de détails.

---

**Note** : Le code HTML pour les pages d'authentification et d'inscription est inspiré de tutoriels YouTube, et non créé de manière originale. Si vous souhaitez personnaliser le design, vous pouvez modifier les fichiers dans le dossier `public`.
