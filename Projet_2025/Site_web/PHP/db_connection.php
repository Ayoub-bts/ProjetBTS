<?php
$servername = "localhost"; // Serveur local
$username = "root"; // Nom d'utilisateur par défaut
$password = ""; // Mot de passe par défaut
$dbname = "projet agricole"; // Nom de la base

// Connexion à la base de données
$conn = new mysqli($servername, $username, $password, $dbname);

// Vérification de la connexion
if ($conn->connect_error) {
    die("Connexion échouée : " . $conn->connect_error);
}
?>
