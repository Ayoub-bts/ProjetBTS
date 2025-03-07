<?php
$servername = "localhost"; // Serveur (local si tu utilises WAMP)
$username = "root"; // Nom d'utilisateur WAMP (par défaut : root)
$password = ""; // Mot de passe (par défaut : vide)
$dbname = "projet agricole"; // Nom de ta base

$conn = new mysqli($servername, $username, $password, $dbname);

// Vérification de la connexion
if ($conn->connect_error) {
    die("Connexion échouée : " . $conn->connect_error);
}

// Requête pour récupérer les données
$sql = "SELECT * FROM humidité ORDER BY Date_heure DESC"; // Adaptez le nom de la table si nécessaire
$result = $conn->query($sql);
?>

<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Historique</title>
    <link rel="stylesheet" href="../CSS/styles.css">
</head>
<body>
    <!-- Header avec l'image en background -->
    <header class="fullscreen-header">
        <img src="../Images et vidéos/fromage.png" alt="Supervision Local Agricole" class="background-image">
        <div class="header-content">
            <h1>Historique des données</h1>
        </div>
    </header>

    <!-- Burger menu -->
    <button class="burger-menu" id="burger-menu">
        ☰
    </button>

    <!-- Navbar -->
    <nav id="navbar" class="hidden">
        <ul>
            <li><a href="../Pages/index.html" class="nav-item" data-active-color="orange">Accueil</a></li>
            <li><a href="../Pages/Visualisation.html" class="nav-item" data-active-color="green">Visualisation des données</a></li>
            <li><a href="../Pages/Alertes.html" class="nav-item" data-active-color="blue">Alertes</a></li>
            <li><a href="../Pages/Historique.php" class="nav-item" data-active-color="red">Historique des données</a></li>
            <li><a href="../Pages/Donnees.html" class="nav-item" data-active-color="purple">Données Enregistrées</a></li>
        </ul>
    </nav>

    <!-- Section principale -->
    <main>
        <h2>Historique des Données</h2>
        <p>Voici les données enregistrées :</p>

        <!-- Tableau dynamique -->
        <table>
            <thead>
                <tr>
                    <th>ID</th>
                    <th>Valeur (Humidité)</th>
                    <th>Date et Heure</th>
                </tr>
            </thead>
            <tbody>
                <?php
                if ($result->num_rows > 0) {
                    while ($row = $result->fetch_assoc()) {
                        echo "<tr>";
                        echo "<td>" . $row['id'] . "</td>";
                        echo "<td>" . $row['Valeur'] . "</td>";
                        echo "<td>" . $row['Date_heure'] . "</td>";
                        echo "</tr>";
                    }
                } else {
                    echo "<tr><td colspan='3'>Aucune donnée disponible</td></tr>";
                }
                ?>
            </tbody>
        </table>

        <!-- Bouton de téléchargement -->
        <div class="download-container">
            <button class="btn-grad">Télécharger les données</button>
        </div>
    </main>

    <!-- Footer -->
    <footer>
        <p>&copy; 2025 Supervision Agricole</p>
    </footer>

    <script src="../JS/script.js" defer></script>
</body>
</html>
